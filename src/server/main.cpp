#include <iostream>
#include "chat.pb.h"

int main() {
    chat::ChatMessage msg;
    msg.set_cmd(chat::MESSAGE);
    msg.set_username("server");
    msg.set_content("hello");

    std::string data;
    msg.SerializeToString(&data);

    std::cout << "Serialized size: " << data.size() << std::endl;

    return 0;
}
