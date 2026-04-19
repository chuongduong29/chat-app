#include "chat_server.h"
#include <boost/asio.hpp>
#include <iostream>

int main() {
    try {
        boost::asio::io_context io_context;

        ChatServer server(io_context, 12345);

        std::cout << "Server running on port 12345..." << std::endl;

        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
