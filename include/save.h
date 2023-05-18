#ifndef __SAVE_H
#define __SAVE_H

#include "typedefs.h"

struct PlayerStatus {
    u16 name[8];
    u32 id;
    u32 money;
    u8  gender;
    u8  regionCode;
    u8  badges;                 // bitmask; use PlayerStatus_CheckBadge to read this
    u8  unionRoomAppearance;
    u8  romCode;                // this should always be 0 for Platinum
    u8  sinnohDexComplete   :1,
        nationalDexActive   :1,
        _dummy1             :6;
    u16 _dummy2;
};

struct PlayerItem {
    u16 id;
    u16 quantity;
};

struct PlayerItems {
    struct PlayerItem normalItems   [165];
    struct PlayerItem keyItems      [50];
    struct PlayerItem tms           [100];
    struct PlayerItem ballSeals     [12];
    struct PlayerItem medicine      [40];
    struct PlayerItem berries       [64];
    struct PlayerItem pokeBalls     [15];
    struct PlayerItem battleItems   [30];
    u32 registeredKeyItem;      // Y/Select
};

enum Badge {
    BADGE_OREBURGH = 0,
    BADGE_ETERNA,
    BADGE_VEILSTONE,
    BADGE_PASTORIA,
    BADGE_HEARTHOME,
    BADGE_CANALAVE,
    BADGE_SNOWPOINT,
    BADGE_SUNYSHORE,
    BADGE_MAX
};

/**
 * @brief Gets the player's current game status.
 * 
 * This includes info like the player's name, their trainer ID, how much
 * money they have, their owned badges, etc.
 * 
 * @param[in] saveData      Player save data.
 * @return                  Player's game status.
 */
struct PlayerStatus* __attribute__((long_call)) SaveData_GetPlayerStatus(void *saveData);

/**
 * @brief Gets the player's owned items.
 * 
 * @param[in] saveData      Player save data.
 * @return                  Player's owned items.
 */
struct PlayerItems* __attribute__((long_call)) SaveData_GetPlayerItems(void *saveData);

/**
 * @brief Checks if a player has a given badge.
 * 
 * @param[in] playerStatus  Player Status from save data.
 * @param[in] badgeID       ID of the badge to check.
 * @return                  TRUE if the badge is owned, FALSE otherwise.
 */
BOOL  __attribute__((long_call)) PlayerStatus_CheckBadge(struct PlayerStatus *playerStatus, int badgeID);

#endif // __SAVE_H