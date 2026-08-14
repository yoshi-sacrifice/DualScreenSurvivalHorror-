#ifndef RE2_TELEMETRY_H
#define RE2_TELEMETRY_H

#include "retroarch_client.h"
#include <cstdint>
#include <utility>

class RE2Telemetry {
public:
    explicit RE2Telemetry(RetroArchClient& client);

    bool fetchStats(uint16_t& out_health, uint8_t& out_handgun_ammo);

private:
    RetroArchClient& client_;
    static constexpr uint32_t HEALTH_OFFSET = 0x000CFD4E;
    static constexpr uint32_t HANDGUN_AMMO_OFFSET = 0x000D4A3D;
};

#endif // RE2_TELEMETRY_H
