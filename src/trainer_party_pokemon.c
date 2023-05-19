#include "config.h"

#ifdef BUGFIX_TRAINER_PARTY_POKEMON

#include "battle.h"
#include "pokemon.h"
#include "sys.h"
#include "trainer.h"
#include "typedefs.h"

#define GENDER_M    0
#define GENDER_F    1
#define GENDER_U    2

struct TrainerPokemon {
    u16 dv;
    u16 level;
    u16 species;
    u16 ballSeal;
};

struct TrainerPokemonWithMoves {
    u16 dv;
    u16 level;
    u16 species;
    u16 moves[4];
    u16 ballSeal;
};

struct TrainerPokemonWithItem {
    u16 dv;
    u16 level;
    u16 species;
    u16 itemID;
    u16 ballSeal;
};

static inline u8 LoadAbilityValue(int species, int form, u8 abilitySlot)
{
    int trueSpecies = Form_CalcTrueSpecies(species, form);

    u8 ability1 = Pokemon_GetBaseStats(trueSpecies, PERSONAL_ABILITY_1);
    u8 ability2 = Pokemon_GetBaseStats(trueSpecies, PERSONAL_ABILITY_2);

    return ((ability2 != 0) && (abilitySlot & 1))
            ? ability2
            : ability1;
}

void Trainer_MakePokemon(struct BattleParams *battleParams, int clientNum, int heapID)
{
    u32 rngSeedOld = RNG_Seed();

    Party_Init(battleParams->party[clientNum], 6);

    u8 *buffer = Malloc(heapID, sizeof(struct TrainerPokemonFull) * 6);
    // void *buffer = Malloc(heapID, sizeof(struct TrainerPokemonFull) * 6);

    Trainer_LoadParty(battleParams->trainerIDs[clientNum], buffer);

    u32 rndGenderOffset = (Trainer_Gender(battleParams->trainerData[clientNum].trainerClass) == GENDER_F)
                        ? 120
                        : 136;
    
    // This is a full rewrite of the original function in order to get rid of the dumb
    // massive switch statement that exists in vanilla Platinum. The approach here is
    // to utilize the flags specified in the trainer data (for loading items and moves)
    // to determine how to parse the raw bytecode.
    //
    // Credits to BluRose and turtleisaac for this code structure. Cool stuff.
    u8  partySize = battleParams->trainerData[clientNum].partySize;
    u16 offset = 0;
    struct Pokemon *party[partySize];

    for (int i = 0; i < partySize; i++) {
        party[i] = Pokemon_Malloc(heapID);

        // IVs and ability slot are stored in a composite byte-pair.
        // The ability slot is defined by bit 8; to specify ability
        // slot 2, for example, the DV value would be 1 + (whatever
        // DV value you would want otherwise).
        //
        // e.g., if you wanted ability slot 2 + 31 in all IVs, you
        // would set DV == 1 + 255 == 256.
        u16 dv          = buffer[offset]
                        | (buffer[offset + 1] << 8); buffer += 2;
        u8  ivs         = dv & 0xFF;
        u8  abilitySlot = (dv & 0x100) >> 8;

        u16 level       = buffer[offset]
                        | (buffer[offset + 1] << 8); buffer += 2;

        // Species and Form are stored in a composite byte-pair
        u16 species     = buffer[offset]
                        | (buffer[offset + 1] << 8); buffer += 2;
        u8  form        = (species & 0xFC00) >> 10;
        species         = (species & 0x03FF);

        u16 item;
        if (battleParams->trainerData[clientNum].dataType & TRAINER_DATA_TYPE_ITEMS) {
            item        = buffer[offset]
                        | (buffer[offset + 1] << 8); buffer += 2;
        }

        u16 moves[4];
        if (battleParams->trainerData[clientNum].dataType & TRAINER_DATA_TYPE_MOVES) {
            for (int j = 0; j < 4; j++) {
                moves[j] = buffer[offset]
                         | (buffer[offset + 1] << 8); buffer += 2;
            }
        }

        u16 ballSeal = buffer[offset]
                     | (buffer[offset + 1] << 8); buffer += 2;

        // Now let's set some data.
        u8 ability = LoadAbilityValue(species, form, abilitySlot);

        u32 rnd = dv
                + level
                + species
                + battleParams->trainerIDs[clientNum];
        RNG_SetSeed(rnd);
        for (int j = 0; j < battleParams->trainerData[clientNum].trainerClass; j++) {
            rnd = RNG_Get();
        }

        rnd = (rnd << 8) + rndGenderOffset;
        ivs = ivs * 31 / 255;

        Pokemon_Init(party[i], species, level, ivs, 1, rnd, 2, 0);
        Pokemon_Set(party[i], MON_PARAM_FORM_NUMBER, &form);
        Pokemon_Set(party[i], MON_PARAM_ABILITY,     &ability);

        if (battleParams->trainerData[clientNum].dataType & TRAINER_DATA_TYPE_ITEMS) {
            Pokemon_Set(party[i], MON_PARAM_HELD_ITEM, &item);
        }

        if (battleParams->trainerData[clientNum].dataType & TRAINER_DATA_TYPE_MOVES) {
            for (int j = 0; j < 4; j++) {
                Pokemon_SetMoveSlot(party[i], moves[j], j);
            }
        }

        Pokemon_Recalc(party[i]);
        Pokemon_AssignBallSeal(ballSeal, party[i], heapID);
    }

    for (int i = 0; i < partySize; i++) {
        Party_Add(battleParams->party[clientNum], party[i]);
        Free(party[i]);
    }

    Free(buffer);
    RNG_SetSeed(rngSeedOld);
}

#endif
