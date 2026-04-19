#pragma once
#include <boost/asio.hpp>
#include "session_manager.h"

using boost::asio::ip::tcp;

class ChatServer {
public:
    ChatServer(boost::asio::io_context& io_context, short port);

private:
    void do_accept();

    tcp::acceptor acceptor_;
    SessionManager manager_;
};
