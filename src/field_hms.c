#include "config.h"

#ifdef FIELD_HMS

#include "typedefs.h"

#include "field.h"
#include "item.h"
#include "party.h"
#include "player.h"
#include "pokemon.h"
#include "save.h"
#include "tile.h"

#include "ui/party_list.h"

#include "constants/moves.h"
#include "constants/scripts.h"

#define HEAP_ID_WORLD   0
#define HM03_SURF       422

u16 ScriptCheck_TalkToTile(struct FieldState *fieldState, u8 nextTile)
{
    // Most of this is just reinventing the wheel from the original function
    // which kinda sucks, but w/e.
    int playerDirection = Player_Direction(fieldState->playerState);

    if (Tile_IsPC(nextTile) && playerDirection == PLAYER_DIR_UP) {
        return SCRIPT_TURN_ON_PC;
    } else if (Tile_IsSmallBookshelf_01(nextTile)) {
        return SCRIPT_SMALL_BOOKSHELF_01;
    } else if (Tile_IsSmallBookshelf_02(nextTile)) {
        return SCRIPT_SMALL_BOOKSHELF_02;
    } else if (Tile_IsBookshelf_01(nextTile)) {
        return SCRIPT_BOOKSHELF_01;
    } else if (Tile_IsBookshelf_02(nextTile)) {
        return SCRIPT_BOOKSHELF_02;
    } else if (Tile_IsTrashcan(nextTile)) {
        return SCRIPT_TRASHCAN;
    } else if (Tile_IsShopBookshelf_01(nextTile)) {
        return SCRIPT_SHOP_BOOKSHELF_01;
    } else if (Tile_IsShopBookshelf_02(nextTile)) {
        return SCRIPT_SHOP_BOOKSHELF_02;
    } else if (Tile_IsShopBookshelf_03(nextTile)) {
        return SCRIPT_SHOP_BOOKSHELF_03;
    } else if (Tile_IsWaterfall(nextTile)) {
        return SCRIPT_WATERFALL;
    } else if (Tile_IsMap(nextTile)) {
        return SCRIPT_TOWNMAP;
    } else if (Tile_IsBumpPost(nextTile)) {
        return SCRIPT_BUMP_POST;
    } else if (Tile_IsTV(nextTile) && playerDirection == PLAYER_DIR_UP) {
        return SCRIPT_TV;
    }

    if (Player_CanRockClimbFromHere(nextTile, playerDirection)) {
        return SCRIPT_ROCK_CLIMB;
    }
    
    // Here's where the actually-modified code starts
    if (Player_Form(fieldState->playerState) != PLAYER_FORM_SWIMMING) {
        struct PlayerStatus *playerStatus = SaveData_GetPlayerStatus(fieldState->saveData);
        u32 currTile = Player_CalcCurrentMapAttributes(fieldState->playerState);

        if (Player_CanSurfFromHere(fieldState->playerState, currTile, nextTile)
                && PlayerStatus_CheckBadge(playerStatus, BADGE_PASTORIA)) {
            if (PlayerItems_HaveAtLeast(SaveData_GetPlayerItems(fieldState->saveData), HM03_SURF, 1, HEAP_ID_WORLD) != 0) {
                return SCRIPT_SURF;
            }
        }
    }

    return 0xFFFF;
}

struct HMListPriority {
    u16 move;
    u16 hmNum;      // zero-indexed
};

static struct HMListPriority sHMList[] = {
    { MOVE_FLY,        1 },
    { MOVE_DEFOG,      4 },
    // Don't show the other HMs since they're just usable via scripts in the overworld
};

// Sticking this here because idk where else to put it
// Simple function, just checks if we're in the salon header.
BOOL __attribute__((long_call)) BattleTower_IsSalon(void *fieldState);

u8 PartyList_MakeFieldMoveMenu(struct PartyList *partyList, u8 *menuParams)
{
    struct Pokemon *pokemon = Party_GetMember(partyList->partyData->party, partyList->selectedPosition);

    u8 menuEntries = 0, fieldMoves = 0;
    menuParams[menuEntries++] = MENU_SUMMARY;

    if (BattleTower_IsSalon(partyList->partyData->fieldState) == FALSE) {
        if (partyList->panels[partyList->selectedPosition].egg == 0) {
            u32 species = Pokemon_Get(pokemon, MON_PARAM_SPECIES,     NULL);
            u32 form    = Pokemon_Get(pokemon, MON_PARAM_FORM_NUMBER, NULL);
            for (int i = 0; i < 2 && fieldMoves < 4; i++) {
                if (Pokemon_CanLearnTM(species, form, 92 + sHMList[i].hmNum)) {
                    u16 move = sHMList[i].move;
                    u8 menuID = PartyList_CalcMenuIDForMove(move);
                    if (menuID != 0xFF) {
                        menuParams[menuEntries++] = menuID;
                        PartyList_LoadMoveMenuString(partyList, move, fieldMoves++);
                    }
                }
            }

            menuParams[menuEntries++] = MENU_ROW;

            if (Item_IsMail(partyList->panels[partyList->selectedPosition].itemID)) {
                menuParams[menuEntries++] = MENU_MAIL;
            } else {
                menuParams[menuEntries++] = MENU_ITEM;
            }
        } else {
            menuParams[menuEntries++] = MENU_ROW;
        }
    }

    menuParams[menuEntries++] = MENU_CANCEL;

    return menuEntries;
}

#endif