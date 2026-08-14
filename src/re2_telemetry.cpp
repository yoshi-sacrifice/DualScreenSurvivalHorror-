#include "re2_telemetry.h"

RE2Telemetry::RE2Telemetry(RetroArchClient& client)
    : client_(client) {}

bool RE2Telemetry::fetchStats(
    uint16_t& out_health,
    uint8_t& out_handgun_ammo,
    uint8_t& out_shotgun_ammo,
    uint8_t& out_equipped_weapon_id
) {
    std::vector<uint8_t> health_bytes;
    if (!client_.readCoreRam(HEALTH_OFFSET, 2, health_bytes) ||
        health_bytes.size() != 2) {
        return false;
    }

    out_health = static_cast<uint16_t>(
        health_bytes[0] | (health_bytes[1] << 8)
    );

    std::vector<uint8_t> handgun_ammo_bytes;
    if (!client_.readCoreRam(HANDGUN_AMMO_OFFSET, 1, handgun_ammo_bytes) ||
        handgun_ammo_bytes.size() != 1) {
        return false;
    }

    out_handgun_ammo = handgun_ammo_bytes[0];

    std::vector<uint8_t> shotgun_ammo_bytes;
    if (!client_.readCoreRam(SHOTGUN_AMMO_OFFSET, 1, shotgun_ammo_bytes) ||
        shotgun_ammo_bytes.size() != 1) {
        return false;
    }

    out_shotgun_ammo = shotgun_ammo_bytes[0];

    std::vector<uint8_t> weapon_bytes;
    if (!client_.readCoreRam(EQUIPPED_WEAPON_OFFSET, 1, weapon_bytes) ||
        weapon_bytes.size() != 1) {
        return false;
    }

    out_equipped_weapon_id = weapon_bytes[0];

    return true;
}
