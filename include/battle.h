#ifndef __BATTLE_H
#define __BATTLE_H

#include "typedefs.h"

#include "party.h"
#include "save.h"
#include "trainer.h"

#define FIGHT_TYPE_SINGLES          (0x00000000)
#define FIGHT_TYPE_WILD             (0x00000000)
#define FIGHT_TYPE_TRAINER          (0x00000001)
#define FIGHT_TYPE_DOUBLES          (0x00000002)
#define FIGHT_TYPE_LINK             (0x00000004)
#define FIGHT_TYPE_FOUR_PLAYER      (0x00000008)
#define FIGHT_TYPE_TWO_ENEMIES      (0x00000010)
#define FIGHT_TYPE_SAFARI           (0x00000020)
#define FIGHT_TYPE_AI               (0x00000040)
#define FIGHT_TYPE_TOWER            (0x00000080)
#define FIGHT_TYPE_ROAMER           (0x00000100)
#define FIGHT_TYPE_PAL_PARK         (0x00000200)
#define FIGHT_TYPE_CATCH_TUTORIAL   (0x00000400)
#define FIGHT_TYPE_DEBUG            (0x80000000)

#define FIGHT_TYPE_WILD_SINGLES         (FIGHT_TYPE_SINGLES | FIGHT_TYPE_WILD)
#define FIGHT_TYPE_WILD_DOUBLES         (FIGHT_TYPE_DOUBLES | FIGHT_TYPE_WILD)
#define FIGHT_TYPE_TRAINER_SINGLES      (FIGHT_TYPE_SINGLES | FIGHT_TYPE_TRAINER)
#define FIGHT_TYPE_TRAINER_DOUBLES      (FIGHT_TYPE_DOUBLES | FIGHT_TYPE_TRAINER)
#define FIGHT_TYPE_AI_TWO_ENEMIES       (FIGHT_TYPE_TRAINER_DOUBLES | FIGHT_TYPE_TWO_ENEMIES | FIGHT_TYPE_AI)
#define FIGHT_TYPE_AI_TWO_ENEMIES_TAG   (FIGHT_TYPE_AI_TWO_ENEMIES | FIGHT_TYPE_FOUR_PLAYER)

/*
 * Singles will only ever have CLIENT_PLAYER and CLIENT_ENEMY:
 * 
 *                  22
 *      11
 * 
 * Doubles will always have all four clients:
 * 
 *              4 2
 *      1 3
 */
#define CLIENT_PLAYER               0
#define CLIENT_ENEMY                1
#define CLIENT_PLAYER_PARTNER       2
#define CLIENT_ENEMY_PARTNER        3
#define CLIENT_MAX                  4

struct BattleParams {
    u32     fightType; // 0x00

    struct Party *party[CLIENT_MAX];    // 0x04

    int     winLoseFlag;        // 0x14
    int     trainerIDs[CLIENT_MAX];  // 0x18
    
    struct TrainerData  trainerData[CLIENT_MAX];    // 0x28
    struct PlayerStatus *playerStatus[CLIENT_MAX];  // 0xF8
    struct PlayerItems  *playerItems;               // 0x108

    void    *bagCursor;
    void    *pokedex;
    void    *box;
    void    *cries[4];
    void    *poketch;
    void    *wifiHistory;
    void    *config;
    void    *tvBattle;
    int     battleTowerRecords[3];
    void    *vsRecorder;
    void    *journal;
    void    *palPad;
    
    int     bgID;
    int     groundID;
    int     locID;
    int     zoneID;

    // and more
};

u32 __attribute__((long_call)) FieldEncounter_GetTrainerSpecialEffects(u32 trainerClass);
u32 __attribute__((long_call)) FieldEncounter_GetPokemonSpecialEffects(struct Party *party, int zoneID);

#endif // __BATTLE_H