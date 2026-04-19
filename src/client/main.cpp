#include "client.h"
#include "chat.pb.h"
#include <iostream>
#include <thread>

int main() {
    try {
        boost::asio::io_context io_context;

        Client client(io_context, "127.0.0.1", 12345);

        std::thread t([&io_context]() {
            io_context.run();
        });

        std::string username;
        std::cout << "Enter username: ";
        std::getline(std::cin, username);

        // gửi JOIN
        chat::ChatMessage join;
        join.set_cmd(chat::JOIN);
        join.set_username(username);

        std::string data;
        join.SerializeToString(&data);
        client.write(data);

        // loop nhập chat
        while (true) {
            std::string line;
            std::getline(std::cin, line);

            chat::ChatMessage msg;
            msg.set_cmd(chat::MESSAGE);
            msg.set_username(username);
            msg.set_content(line);

            std::string out;
            msg.SerializeToString(&out);

            client.write(out);
        }

        t.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
