#ifndef __PARTY_H
#define __PARTY_H

#include "pokemon.h"

struct Party {
    int maxMembers;
    int countMembers;
    struct Pokemon members[6];
};

struct PartyData {
    struct Party *party;

    void *items;
    void *mail;
    void *config;
    u8   padding_x10[3];
    void *fieldState;

    // and more
};

/**
 * @brief Get a Pokemon from the party structure at a given position.
 * 
 * Original Function: [`GetAdrOfPkmnInParty @ 0x0207A0FC` (ARM9)](https://github.com/JimB16/PokePlat/blob/ccbdf7ea8b08f23d3adcb6baa7d1f2b8dc24bbc1/source/arm9_pkmnparty.s#L223)
 * 
 * @param[in]  party
 * @param[in]  pos      The slot to retrieve. Zero-indexed (`pos == 0` returns slot 1, etc.)
 * @return              Address of the Pokemon in that slot.
 */
struct Pokemon* __attribute__((long_call)) Party_GetMember(struct Party *party, int pos);

#endif // __PARTY_H