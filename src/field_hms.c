#include "config.h"

#ifdef FIELD_HMS

#include "typedefs.h"

#include "field.h"
#include "item.h"
#include "party.h"
#include "player.h"
#include "pokemon.h"
#include "save.h"

#include "ui/party_list.h"

#include "constants/moves.h"

#define HEAP_ID_WORLD   0

#define HM03_SURF       422

#define SCRIPT_ID_SURF_PROMPT 10004

// This needs an update to the Surfing script (Script 5 in file 409)
// Gotta figure out how to piece that into the build before building the hook
#if 0
u16 FieldHMs_Surf(struct FieldState *fieldState, u8 nextAttr)
{
    if (Player_Form(fieldState->playerState) != 2) {        // Player is not swimming
        void *flags = SaveData_GetFlags(fieldState->saveData);
        u32 currAttr = Player_CalcCurrentMapAttributes(fieldState->playerState);
        if (Player_CanSurfFromHere(fieldState->playerState, currAttr, nextAttr) && Flags_CheckBadge(flags, 3)) {
            if (Items_HaveAtLeast(SaveData_GetItems(fieldState->saveData), HM03_SURF, 1, HEAP_ID_WORLD) != 0) {
                return SCRIPT_ID_SURF_PROMPT;
            }
        }
    }

    return (u16) ~0;
}
#endif

struct HMListPriority {
    u16 move;
    u16 hmNum;      // zero-indexed
};

static struct HMListPriority sHMList[] = {
    { MOVE_FLY,        1 },
    { MOVE_DEFOG,      4 },
    { MOVE_CUT,        0 },
    { MOVE_SURF,       2 },
    { MOVE_STRENGTH,   3 },
    { MOVE_ROCK_SMASH, 5 },
    { MOVE_WATERFALL,  6 },
    { MOVE_ROCK_CLIMB, 7 },
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
            for (int i = 0; i < 8 && fieldMoves < 4; i++) {
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