#include "retroarch_client.h"
#include "re2_telemetry.h"

#include <chrono>
#include <csignal>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

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
        uint8_t shotgun_ammo = 0;
        uint8_t equipped_weapon_id = 0;

        if (telemetry.fetchStats(
                health,
                handgun_ammo,
                shotgun_ammo,
                equipped_weapon_id)) {

            std::string weapon_name = "Unknown";
            std::string ammo_display = "?";

            switch (equipped_weapon_id) {
                case 0x01:
                    weapon_name = "Knife";
                    ammo_display = "--";
                    break;

                case 0x02:
                    weapon_name = "Handgun";
                    ammo_display = std::to_string(handgun_ammo);
                    break;

                case 0x07:
                    weapon_name = "Shotgun";
                    ammo_display = std::to_string(shotgun_ammo);
                    break;

                default:
                    break;
            }

            std::cout
                << "\r[TELEMETRY] Status: CONNECTED"
                << " | Health: " << health
                << " | Weapon: 0x"
                << std::hex
                << std::uppercase
                << static_cast<int>(equipped_weapon_id)
                << std::dec
                << " (" << weapon_name << ")"
                << " | Ammo: " << ammo_display
                << "          "
                << std::flush;

        } else {
            std::cout
                << "\r[TELEMETRY] Status: WAITING / RETROARCH OFFLINE..."
                << "                              "
                << std::flush;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }

    std::cout << "\nExiting cleanly.\n";
    return 0;
}
