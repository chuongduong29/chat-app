#include "session.h"
#include "session_manager.h"
#include <iostream>

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
                std::string data(buffer_.begin(), buffer_.begin() + length);
                std::cout << "Received: " << data << std::endl;

                do_read(); // loop
            } else {
                stop(); // QUAN TRỌNG
            }
        }
    );
}
