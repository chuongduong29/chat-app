#include <iostream>
#include "chat.pb.h"

int main() {
    chat::ChatMessage msg;
    msg.set_cmd(chat::JOIN);
    msg.set_username("client");

    std::string data;
    msg.SerializeToString(&data);

    chat::ChatMessage parsed;
    parsed.ParseFromString(data);

    std::cout << "Username: " << parsed.username() << std::endl;

    return 0;
}
