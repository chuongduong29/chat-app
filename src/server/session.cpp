#include "session.h"
#include "session_manager.h"
#include <iostream>
#include "../common/message_framer.h"
#include "chat.pb.h"

Session::Session(tcp::socket socket, SessionManager& manager)
    : socket_(std::move(socket)), buffer_(1024), manager_(manager) {}

void Session::start() {
    manager_.join(shared_from_this());
    std::cout << "Client connected" << std::endl;
    do_read();
}

void Session::stop() {
    manager_.leave(shared_from_this());
    socket_.close();
    std::cout << "Client disconnected" << std::endl;
}

void Session::do_read() {
    auto self(shared_from_this());

    socket_.async_read_some(
        boost::asio::buffer(buffer_),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                // append vào read buffer
                read_buf_.insert(read_buf_.end(), buffer_.begin(), buffer_.begin() + length);

                std::string msg_data;

                // parse nhiều message nếu có
                while (MessageFramer::unpack(read_buf_, msg_data)) {
                    chat::ChatMessage msg;

                    if (msg.ParseFromString(msg_data)) {
                        //// xử lý message
                        //std::cout << "Received: " << msg.content() << std::endl;
                        switch (msg.cmd()) {
                            case chat::JOIN:
                                std::cout << msg.username() << " joined\n";
                                break;

                            case chat::MESSAGE:
                                std::cout << msg.username() << ": " << msg.content() << std::endl;
                                break;

                            case chat::LEAVE:
                                stop();
                                break;
                        }

                        manager_.broadcast(msg_data, shared_from_this());
                    } else {
                        std::cout << "Invalid protobuf" << std::endl;
                    }
                }

                do_read();
            } else {
                stop();
            }
        }
    );
}

void Session::send(const std::string& data) {
    auto self(shared_from_this());

    boost::asio::post(socket_.get_executor(),
        [this, self, data]() {
            bool write_in_progress = !write_queue_.empty();

            // pack trước khi gửi
            auto packed = MessageFramer::pack(data);
            write_queue_.push(std::string(packed.begin(), packed.end()));

            if (!write_in_progress) {
                do_write();
            }
        }
    );
}

void Session::do_write() {
    auto self(shared_from_this());

    boost::asio::async_write(
        socket_,
        boost::asio::buffer(write_queue_.front()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                write_queue_.pop();

                if (!write_queue_.empty()) {
                    do_write();
                }
            } else {
                stop();
            }
        }
    );
}
