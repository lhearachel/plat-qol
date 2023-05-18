#ifndef __PLAYER_H
#define __PLAYER_H

#include "typedefs.h"

enum PlayerForm {
    PLAYER_FORM_NORMAL = 0,
    PLAYER_FORM_CYCLING,
    PLAYER_FORM_SWIMMING,
    PLAYER_FORM_MAX
};

enum PlayerDirection {
    PLAYER_DIR_UP = 0,
    PLAYER_DIR_DOWN,
    PLAYER_DIR_LEFT,
    PLAYER_DIR_RIGHT,
    PLAYER_DIR_MAX
};

/**
 * @brief Gets the player's current form in the overworld.
 * 
 * See enum PlayerForm.
 * 
 * @param[in] playerState
 * @return                  An int representing the player's current overworld form.
 */
int __attribute__((long_call)) Player_Form(void *playerState);

/**
 * @brief Gets the player's current directional-facing in the overworld.
 * 
 * See enum PlayerDirection.
 * 
 * @param[in] playerState
 * @return                  An int representing the player's current overworld direction.
 */
int __attribute__((long_call)) Player_Direction(void *playerState);

/**
 * @brief Gets the map attributes of the player's currently-occupied tile.
 * 
 * @param[in] playerState
 * @return                  Map attributes of the player's currently-occupied tile.
 */
u32 __attribute__((long_call)) Player_CalcCurrentMapAttributes(void *playerState);

/**
 * @brief Checks if the player can rock climb from their current tile in the
 * direction that they are facing.
 * 
 * @param[in] nextTile          Map attributes of the tile directly in front of the player.
 * @param[in] playerDirection   Direction the player is facing.
 * @return                      TRUE if the player can use Rock Climb, FALSE otherwise.
 */
BOOL __attribute__((long_call)) Player_CanRockClimbFromHere(u32 nextTile, int playerDirection);

/**
 * @brief Checks if the player can surf from their current tile onto the next
 * tile.
 * 
 * This performs a few extra checks internally, e.g. if the player is on a
 * bridge and such.
 * 
 * @param[in] playerState
 * @param[in] currTile      Map attributes of the player's currently-occupied tile.
 * @param[in] nextTile      Map attributes of the tile directly in front of the player.
 * @return                  TRUE if the player can surf from their tile, FALSE otherwise.
 */
BOOL __attribute__((long_call)) Player_CanSurfFromHere(void *playerState, u32 currTile, u32 nextTile);

#endif // __PLAYER_H