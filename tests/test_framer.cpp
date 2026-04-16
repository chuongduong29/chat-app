#include "../src/common/message_framer.h"

#include <iostream>
#include <vector>

int main() {
    std::vector<uint8_t> buffer;
    std::string out;

    // =========================
    // Test 1: basic pack/unpack
    // =========================
    auto data = MessageFramer::pack("hello");
    buffer.insert(buffer.end(), data.begin(), data.end());

    if (MessageFramer::unpack(buffer, out)) {
        std::cout << "Test1: " << out << std::endl;
    }

    // =========================
    // Test 2: multiple messages
    // =========================
    auto d1 = MessageFramer::pack("A");
    auto d2 = MessageFramer::pack("B");

    buffer.insert(buffer.end(), d1.begin(), d1.end());
    buffer.insert(buffer.end(), d2.begin(), d2.end());

    while (MessageFramer::unpack(buffer, out)) {
        std::cout << "Test2: " << out << std::endl;
    }

    // =========================
    // Test 3: partial message
    // =========================
    auto full = MessageFramer::pack("hello_world");

    buffer.clear();
    buffer.insert(buffer.end(), full.begin(), full.begin() + 3);

    if (!MessageFramer::unpack(buffer, out)) {
        std::cout << "Test3: waiting..." << std::endl;
    }

    buffer.insert(buffer.end(), full.begin() + 3, full.end());

    if (MessageFramer::unpack(buffer, out)) {
        std::cout << "Test3: " << out << std::endl;
    }

    return 0;
}
