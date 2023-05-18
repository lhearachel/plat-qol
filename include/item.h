#ifndef __ITEM_H
#define __ITEM_H

#include "typedefs.h"

/**
 * @brief Checks if a given item is mail.
 * 
 * @param[in] itemID   ID of the item.
 * @return             TRUE if the item is mail, FALSE otherwise.
 */
BOOL __attribute__((long_call)) Item_IsMail(u16 itemID);

/**
 * @brief Checks if the player has a certain amount of a given item.
 * 
 * @param[in] items     Pointer to the player's owned items.
 * @param[in] itemID    ID of the item to check for.
 * @param[in] quantity  Quantity of the item required.
 * @param[in] heapID    Heap ID for extra memory allocation.
 * @return              TRUE if the player has the requisite amount of the item, FALSE otherwise.
 */
BOOL __attribute__((long_call)) Items_HaveAtLeast(void *items, u16 itemID, u16 quantity, u32 heap);

#endif