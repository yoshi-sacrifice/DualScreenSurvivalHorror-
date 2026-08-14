#include "re2_telemetry.h"

RE2Telemetry::RE2Telemetry(RetroArchClient& client) : client_(client) {}

bool RE2Telemetry::fetchStats(uint16_t& out_health, uint8_t& out_handgun_ammo) {
    std::vector<uint8_t> health_bytes;
    if (client_.readCoreRam(HEALTH_OFFSET, 2, health_bytes) && health_bytes.size() == 2) {
        out_health = static_cast<uint16_t>(health_bytes[0] | (health_bytes[1] << 8));
    } else {
        return false;
    }

    std::vector<uint8_t> ammo_bytes;
    if (client_.readCoreRam(HANDGUN_AMMO_OFFSET, 1, ammo_bytes) && ammo_bytes.size() == 1) {
        out_handgun_ammo = ammo_bytes[0];
    } else {
        return false;
    }

    return true;
}
