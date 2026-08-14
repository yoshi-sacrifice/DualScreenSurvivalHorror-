#include "retroarch_client.h"
#include "re2_telemetry.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>

static volatile std::sig_atomic_t keep_running = 1;

void signal_handler(int) {
    keep_running = 0;
}

int main() {
    std::signal(SIGINT, signal_handler);

    std::cout << "Starting DualScreen Survival Horror Proof of Concept...\n";
    std::cout << "Connecting to RetroArch at 127.0.0.1:55355\n";
    std::cout << "Target: Resident Evil 2 (SLUS-00748)\n";
    std::cout << "Press Ctrl+C to exit.\n\n";

    RetroArchClient ra_client("127.0.0.1", 55355);
    RE2Telemetry telemetry(ra_client);

    while (keep_running) {
        uint16_t health = 0;
        uint8_t handgun_ammo = 0;

        if (telemetry.fetchStats(health, handgun_ammo)) {
            std::cout << "\r[TELEMETRY] Status: CONNECTED | Leon Health: " 
                      << health << "   | Handgun Ammo: " << static_cast<int>(handgun_ammo) << "   " << std::flush;
        } else {
            std::cout << "\r[TELEMETRY] Status: WAITING / RETROARCH OFFLINE...              " << std::flush;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "\nExiting cleanly.\n";
    return 0;
}
