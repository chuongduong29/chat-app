#include "message_framer.h"

#include <cstring>      // memcpy
#include <arpa/inet.h>  // htonl, ntohl

// Maximum allowed message size (safety limit)
static constexpr uint32_t MAX_MESSAGE_SIZE = 10 * 1024 * 1024; // 10 MB

std::vector<uint8_t> MessageFramer::pack(const std::string& data) {
    uint32_t len = static_cast<uint32_t>(data.size());

    // Convert length to network byte order (big endian)
    uint32_t net_len = htonl(len);

    std::vector<uint8_t> result;
    result.resize(4 + len);

    // Copy length header
    std::memcpy(result.data(), &net_len, 4);

    // Copy payload data
    std::memcpy(result.data() + 4, data.data(), len);

    return result;
}

bool MessageFramer::unpack(std::vector<uint8_t>& buffer, std::string& out) {
    // Need at least 4 bytes to read length header
    if (buffer.size() < 4) {
        return false;
    }

    uint32_t net_len = 0;
    std::memcpy(&net_len, buffer.data(), 4);

    // Convert from network byte order
    uint32_t len = ntohl(net_len);

    // Security check: invalid or too large message
    if (len == 0 || len > MAX_MESSAGE_SIZE) {
        return false;
    }

    // Wait until full message arrives
    if (buffer.size() < 4 + len) {
        return false;
    }

    // Extract payload
    out.assign(buffer.begin() + 4, buffer.begin() + 4 + len);

    // Remove consumed bytes from buffer
    buffer.erase(buffer.begin(), buffer.begin() + 4 + len);

    return true;
}
