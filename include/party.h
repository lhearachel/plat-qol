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
    void *tv;
    void *rules;
    void *scwk;
    struct FieldState *fieldState;

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

/**
 * @brief Initialize a new Party with enough memory to fit a number of members.
 * 
 * @param[in]  party
 * @param[in]  size     The number of members to allocate for.
 */
void __attribute__((long_call)) Party_Init(struct Party *party, int size);

/**
 * @brief Add a Pokemon to the party.
 * 
 * @param[in]   party
 * @param[in]   pokemon
 */
void __attribute__((long_call)) Party_Add(struct Party *party, struct Pokemon *pokemon);

#endif // __PARTY_H