# Telemetry Specifications

* **Game**: Resident Evil 2 - Dual Shock Ver. (USA) (Disc 1)
* **Region/Serial**: SLUS-00748
* **Core**: SwanStation

## Verified Addresses & Experimental Evidence

### Leon Health

* **PS1/GameShark**: `0x800CFD4E`
* **READ_CORE_RAM**: `0x000CFD4E`
* **Type**: `uint16`, little-endian
* **Observed Data**:
  * `C8 00` = 200 decimal (full health)
  * `8C 00` = 140 decimal (after zombie damage)

### Leon Handgun Ammo

* **PS1/GameShark**: `0x800D4A3D`
* **READ_CORE_RAM**: `0x000D4A3D`
* **Type**: `uint8`
* **Observed Data**:
  * `0x12` = 18 rounds
  * One handgun shot fired
  * `0x11` = 17 rounds

### Leon Equipped Weapon ID

* **READ_CORE_RAM**: `0x000D5BFA`
* **Type**: `uint8`
* **Status**: High confidence / experimentally verified for Knife and Handgun only
* **Observed Data**:
  * `0x01` = Knife equipped
  * `0x02` = Handgun equipped
  * Switching back to handgun returned `0x02`

No other weapon IDs are currently considered verified.
