#ifndef RETROARCH_CLIENT_H
#define RETROARCH_CLIENT_H

#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>

class RetroArchClient {
public:
    RetroArchClient(const std::string& host = "127.0.0.1", uint16_t port = 55355);
    ~RetroArchClient();

    bool readCoreRam(uint32_t offset, std::size_t size, std::vector<uint8_t>& out_data);

private:
    std::string host_;
    uint16_t port_;
    int sockfd_;
    bool initialized_;
};

#endif // RETROARCH_CLIENT_H
