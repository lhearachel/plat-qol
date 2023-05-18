#ifndef __PARTY_LIST_H
#define __PARTY_LIST_H

#include "typedefs.h"

#include "party.h"

enum PartyListMenuEntries {
    MENU_ROW = 0,
    MENU_SUMMARY,
    MENU_ITEM,
    MENU_ITEM_SET,
    MENU_ITEM_GIVE,
    MENU_MAIL,
    MENU_MAIL_READ,
    MENU_MAIL_GIVE,
    MENU_DAYCARE_GIVE,
    MENU_CANCEL,
    MENU_CHANGE_ORDER,
    MENU_BATTLE_SWITCH,
    MENU_BATTLE_CANCEL,
    MENU_CONTEST_SWITCH,
    MENU_CAPSULE_SET,
    MENU_GURU,

    MENU_MOVE_CUT,
    MENU_MOVE_FLY,
    MENU_MOVE_SURF,
    MENU_MOVE_STRENGTH,
    MENU_MOVE_DEFOG,
    MENU_MOVE_ROCK_SMASH,
    MENU_MOVE_WATERFALL,
    MENU_MOVE_ROCK_CLIMB,

    MENU_MOVE_FLASH,
    MENU_MOVE_TELEPORT,
    MENU_MOVE_DIG,
    MENU_MOVE_SWEET_SCENT,
    MENU_MOVE_CHATTER,
    MENU_MOVE_MILK_DRINK,
    MENU_MOVE_SOFT_BOILED,

    MENU_STR_MAX = MENU_MOVE_CUT + 4
};

struct PartyListPanelData {
    void *name;
    u16  species;
    u16  curHP;
    u16  maxHP;
    u16  level;
    u16  itemID;
    u16  status     :12,
         showGender  :1,
         gender      :2,
         contest     :1;
    u8   egg;
    u8   form;
    u16  customBallID;

    s8   panelPosX;
    s8   panelPosY;
    s16  pokemonPosX;
    s16  pokemonPosY;
    s16  statusPosX;
    s16  statusPosY;
    s16  itemPosX;
    s16  itemPosY;

    void *icon;
    u8   frameCount;
    u8   flag;
};

struct PartyList {
    u8  padding_x0[0x5A4];

    struct PartyData *partyData;

    u8  padding_x5A8[0x704 - 0x5A8];

    struct PartyListPanelData panels[6];

    u8  padding_x81C[0xB29-0x80C];

    u8  selectedPosition;
};

/**
 * @brief Computes the menu ID for a given move, if any.
 * 
 * See: enum PartyListMenuEntries.
 * 
 * @param[in] moveID    ID of the move.
 * @return              The entry in PartyListMenuEntries corresponding to the move, if any.
 */
u8   __attribute__((long_call)) PartyList_CalcMenuIDForMove(u16 moveID);

/**
 * @brief Loads a string for a given move into the submenu for this party list.
 * 
 * @param[in,out] partyList 
 * @param[in]     moveID    ID of the move to load.
 * @param[in]     position  Slot in the menu where the loaded buffer should be placed.
 */
void __attribute__((long_call)) PartyList_LoadMoveMenuString(struct PartyList *partyList, u16 moveID, u8 position);

/**
 * @brief Builds the field submenu for a given Pokemon in the party.
 * 
 * This is the menu that shows up when you select a Pokemon in the party list.
 * 
 * @param[in,out] partyList
 * @param[in,out] menuParams    A list of values from PartyListMenuEntries which describes the submenu.
 * @return                      The final size of menuParams.
 */
u8   __attribute__((long_call)) PartyList_MakeFieldMoveMenu(struct PartyList *partyList, u8 *menuParams);

#endif // __PARTY_LIST_H