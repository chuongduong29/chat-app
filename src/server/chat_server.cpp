#include "chat_server.h"
#include "session.h"

ChatServer::ChatServer(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    do_accept();
}

void ChatServer::do_accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(
                    std::move(socket), manager_
                )->start();
            }

            do_accept();
        }
    );
}
