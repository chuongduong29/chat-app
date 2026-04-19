#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include <queue>
#include <string>

using boost::asio::ip::tcp;

class SessionManager;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, SessionManager& manager);

    void start();
    void send(const std::string& data); // NEW

private:
    void do_read();
    void do_write();
    void stop();

    tcp::socket socket_;
    std::vector<uint8_t> buffer_;     // temp read buffer
    std::vector<uint8_t> read_buf_;   // accumulate buffer

    std::queue<std::string> write_queue_; // IMPORTANT
    bool writing_ = false;

    SessionManager& manager_;
};
