#ifndef __TRAINER_H
#define __TRAINER_H

#include "typedefs.h"

#define TRAINER_DATA_TYPE_BASIC     0x00
#define TRAINER_DATA_TYPE_MOVES     0x01
#define TRAINER_DATA_TYPE_ITEMS     0x02

struct TrainerData {
    u8      dataType;           // 0x00
    u8      trainerClass;       // 0x01
    u8      trainerSpriteIdx;   // 0x02
    u8      partySize;          // 0x03

    u16     bagItems[4];        // 0x04

    u32     aiBitmask;          // 0x0C
    u32     fightType;          // 0x10

    u16     name[8];            // 0x14
    u8      _winMessagePad[8];  // 0x24
    u8      _loseMessagePad[8]; // 0x2C
};  // size == 0x34

// This struct is not actually used anywhere; it instead is
// used just to allocate the total size of a trainer party
// when parsing a trainer battle's enemy Pokemon.
struct TrainerPokemonFull {
    u16 dv;
    u16 level;
    u16 species;
    u16 itemID;
    u16 moves[4];
    u16 ballSeal;
};

void __attribute__((long_call)) Trainer_LoadParty(int trainerID, void *partyBuffer);
u8   __attribute__((long_call)) Trainer_Gender(int trainerClass);

#endif // __TRAINER_H