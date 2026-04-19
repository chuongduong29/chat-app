#include "client.h"
#include "../common/message_framer.h"
#include "chat.pb.h"
#include <iostream>
#include <queue>

Client::Client(boost::asio::io_context& io_context,
               const std::string& host,
               short port)
    : socket_(io_context), buffer_(1024) {

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, std::to_string(port));

    boost::asio::connect(socket_, endpoints);

    do_read();
}

void Client::do_read() {
    socket_.async_read_some(
        boost::asio::buffer(buffer_),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                read_buf_.insert(read_buf_.end(),
                                 buffer_.begin(),
                                 buffer_.begin() + length);

                std::string msg_data;

                while (MessageFramer::unpack(read_buf_, msg_data)) {
                    chat::ChatMessage msg;

                    if (msg.ParseFromString(msg_data)) {
                        std::cout << msg.username()
                                  << ": "
                                  << msg.content()
                                  << std::endl;
                    }
                }

                do_read();
            }
        }
    );
}

void Client::write(const std::string& msg_data) {
    boost::asio::post(socket_.get_executor(),
        [this, msg_data]() {
            bool writing = !write_queue_.empty();

            auto packed = MessageFramer::pack(msg_data);
            write_queue_.push(std::string(packed.begin(), packed.end()));

            if (!writing) {
                do_write();
            }
        });
}

void Client::do_write() {
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(write_queue_.front()),
        [this](boost::system::error_code ec, std::size_t) {
            if (!ec) {
                write_queue_.pop();

                if (!write_queue_.empty()) {
                    do_write();
                }
            }
        }
    );
}

