#pragma once
#include <vector>
#include <string>
#include <cstdint>

class MessageFramer {
public:
    static std::vector<uint8_t> pack(const std::string& data);
    static bool unpack(std::vector<uint8_t>& buffer, std::string& out);
};
