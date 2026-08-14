#include "retroarch_client.h"
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

RetroArchClient::RetroArchClient(const std::string& host, uint16_t port)
    : host_(host), port_(port), sockfd_(-1), initialized_(false) {
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ >= 0) {
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        setsockopt(sockfd_, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
        initialized_ = true;
    }
}

RetroArchClient::~RetroArchClient() {
    if (sockfd_ >= 0) {
        close(sockfd_);
    }
}

bool RetroArchClient::readCoreRam(uint32_t offset, std::size_t size, std::vector<uint8_t>& out_data) {
    if (!initialized_) return false;

    std::stringstream cmd_stream;
    cmd_stream << "READ_CORE_RAM " << std::hex << std::uppercase << offset << " " << std::dec << size;
    std::string command = cmd_stream.str();

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_);
    if (inet_pton(AF_INET, host_.c_str(), &serv_addr.sin_addr) <= 0) {
        return false;
    }

    ssize_t sent = sendto(sockfd_, command.c_str(), command.length(), 0,
                          (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (sent < 0) {
        return false;
    }

    char buffer[1024];
    socklen_t addr_len = sizeof(serv_addr);
    ssize_t received = recvfrom(sockfd_, buffer, sizeof(buffer) - 1, 0,
                                (struct sockaddr*)&serv_addr, &addr_len);
    if (received < 0) {
        return false;
    }

    buffer[received] = '\0';
    std::string resp(buffer);

    std::stringstream ss(resp);
    std::string prefix, addr_str;
    ss >> prefix >> addr_str;

    if (prefix != "READ_CORE_RAM") {
        return false;
    }

    out_data.clear();
    std::string byte_str;
    while (ss >> byte_str) {
        try {
            uint8_t byte_val = static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));
            out_data.push_back(byte_val);
        } catch (...) {
            break;
        }
    }

    return out_data.size() == size;
}
