#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <vector>

using boost::asio::ip::tcp;

class SessionManager;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, SessionManager& manager);

    void start();

private:
    void do_read();
    void stop();

    tcp::socket socket_;
    std::vector<uint8_t> buffer_;
    SessionManager& manager_;
};
