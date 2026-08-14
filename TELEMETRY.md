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

### Leon Shotgun Ammo

* **READ_CORE_RAM**: `0x000D4A45`
* **Type**: `uint8`
* **Status**: Experimentally verified
* **Observed Data**:
  * `0x03` = 3 shells
  * Fired one shotgun shell
  * `0x02` = 2 shells

### Verified Equipped Weapon IDs

* `0x01` = Knife
* `0x02` = Handgun
* `0x07` = Shotgun

Weapon-aware terminal display has been verified as:

* Knife -> `Ammo: --`
* Handgun -> handgun ammunition field
* Shotgun -> shotgun ammunition field

### Health Edge Case

Leon was observed alive in the Danger state while the raw health field at
`0x000CFD4E` contained `00 00` (0 decimal).

Therefore, raw health value `0` must not currently be interpreted as proof that
the player is dead. Death/status semantics require further investigation.
