#pragma once
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <queue>
#include <string>

using boost::asio::ip::tcp;

class Client {
public:
    Client(boost::asio::io_context& io_context,
           const std::string& host,
           short port);

    void write(const std::string& msg);
    void close();

private:
    void do_read();
    void do_write();

    tcp::socket socket_;
    std::vector<uint8_t> buffer_;
    std::vector<uint8_t> read_buf_;

    std::queue<std::string> write_queue_;
};
