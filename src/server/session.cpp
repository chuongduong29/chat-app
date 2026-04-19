#include "session.h"
#include <iostream>

Session::Session(tcp::socket socket)
    : socket_(std::move(socket)), buffer_(1024) {}

void Session::start() {
    std::cout << "Client connected" << std::endl;
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());

    socket_.async_read_some(
        boost::asio::buffer(buffer_.data(), 1024),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "Received: " << length << " bytes" << std::endl;

                // TODO: sau này sẽ đưa vào MessageFramer
                std::string data(buffer_.begin(), buffer_.begin() + length);
                std::cout << data << std::endl;

                do_read(); // loop
            } else {
                std::cout << "Client disconnected" << std::endl;
            }
        }
    );
}
