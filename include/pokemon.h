#ifndef __POKEMON_H
#define __POKEMON_H

#include "typedefs.h"

struct PokemonDataBlockA {
    u16 species;
    u16 heldItem;
    u32 otID;           // low half: visible ID; high half: secret ID
    u32 exp;
    u8  friendship;
    u8  ability;
    u8  markings;       // bitmask for circle, triangle, square, heart, star, diamond
    u8  countryCode;
    u8  hpEV;
    u8  attackEV;
    u8  defenseEV;
    u8  speedEV;
    u8  spAttackEV;
    u8  spDefenseEV;
    u8  coolStat;
    u8  beautyStat;
    u8  cuteStat;
    u8  smartStat;
    u8  toughStat;
    u8  sheen;
    u32 sinnohRibbons;
};

struct PokemonDataBlockB {
    u16 moves[4];
    u8  movePP[4];
    u8  movePPUps[4];

    u32 hpIV        :5,
        attackIV    :5,
        defenseIV   :5,
        speedIV     :5,
        spAttackIV  :5,
        spDefenseIV :5,
        isEgg       :1,
        isNicknamed :1;
    u32 oldRibbons;         // ribbons from gen 3

    u8  eventDistributed    :1,
        sex                 :2,
        formNumber          :5;

    u8  _dummyB_1;
    u16 _dummyB_2;

    u16 newCatchLocation;   // These fields are only used for riddles (Trick House?)
    u16 newHatchLocation;
};

struct PokemonDataBlockC {
    u16 nickname[11];
    u8  originCountryCode;
    u8  originGame;
    u64 sinnohContestRibbons;
};

struct PokemonDataBlockD {
    u16 oTrainerName[8];       // 7 characters + terminator

    u8  caughtYear;
    u8  caughtMonth;
    u8  caughtDay;

    u8  birthYear;
    u8  birthMonth;
    u8  birthDay;

    u16 caughtLocation;
    u16 hatchLocation;

    u8  pokerus;
    u8  pokeball;
    u8  metLevel:7,
        metGender:1;
    u8  encounterType;

    u16 _dummyC;
};

typedef union {
    struct PokemonDataBlockA blockA;
    struct PokemonDataBlockB blockB;
    struct PokemonDataBlockC blockC;
    struct PokemonDataBlockD blockD;
} PokemonDataBlock;

struct BoxPokemon {
    u32 pid;
    u16 partyLock:1,
        boxLock:1,
        badEgg:1,
        _dummyD:13;     // maybe used for some validation checks?
    u16 checksum;       // stored checksum
    PokemonDataBlock substructs[4];
};

struct PartyPokemon {
    u32 condition;      // slp:3, psn:1, brn:1, frz:1, prz:1, tox:1, ...
    u8  level;
    u8  customBallID;
    u16 currentHP;
    u16 maxHP;
    u16 attack;
    u16 defense;
    u16 speed;
    u16 spAttack;
    u16 spDefense;
    u8  mailData[0x35];
    u8  customBalls[0x18];
};

struct Pokemon {
    struct BoxPokemon   boxParams;      // a set of parameters that are applicable at all times for a given individual
    struct PartyPokemon partyParams;    // a set of parameters that are only applicable when in the party
};

enum PokemonDataField {
    // BoxPokemon header fields
	MON_PARAM_PID = 0,
	MON_PARAM_PARTY_LOCK,
    MON_PARAM_BOX_LOCK,
	MON_PARAM_BAD_EGG,
	MON_PARAM_CHECKSUM,

    // BoxPokemon Block A data
    MON_PARAM_SPECIES,
	MON_PARAM_HELD_ITEM,
	MON_PARAM_OT_ID,
	MON_PARAM_EXP,
	MON_PARAM_FRIENDSHIP,
	MON_PARAM_ABILITY,
	MON_PARAM_MARKINGS,
	MON_PARAM_COUNTRY_CODE,
    
	MON_PARAM_HP_EV,            // EVs
	MON_PARAM_ATTACK_EV,
	MON_PARAM_DEFENSE_EV,
	MON_PARAM_SPEED_EV,
	MON_PARAM_SPATTACK_EV,
	MON_PARAM_SPDEFENSE_EV,

	MON_PARAM_COOL,             // contest stats
	MON_PARAM_BEAUTY,
	MON_PARAM_CUTE,
	MON_PARAM_SMART,
	MON_PARAM_TOUGH,
	MON_PARAM_SHEEN,

	MON_PARAM_SINNOH_CHAMPION_RIBBON,               // enter the Hall of Fame
	MON_PARAM_SINNOH_BATTLE_TOWER_ABILITY,          // win a 21 singles streak at the Battle Tower
	MON_PARAM_SINNOH_BATTLE_TOWER_GREAT_ABILITY,    // win a 49 singles streak at the Battle Tower
	MON_PARAM_SINNOH_BATTLE_TOWER_DOUBLE_ABILITY,   // start a double battle set at 49+ battle streak
	MON_PARAM_SINNOH_BATTLE_TOWER_MULTI_ABILITY,    // start a multi battle set with an NPC partner at 49+ battle streak
	MON_PARAM_SINNOH_BATTLE_TOWER_PAIR_ABILITY,     // start a multi battle set by connecting to another game at 49+ battle streak
	MON_PARAM_SINNOH_BATTLE_TOWER_WORLD_ABILITY,    // win a set of seven battles in a wi-fi room at Battle Tower
	MON_PARAM_SINNOH_ALERT_RIBBON,                  // given on Mondays to the first slot in the party
    MON_PARAM_SINNOH_SHOCK_RIBBON,                  // given on Tuesdays to the first slot in the party
	MON_PARAM_SINNOH_DOWNCAST_RIBBON,               // given on Wednesdays to the first slot in the party
	MON_PARAM_SINNOH_CARELESS_RIBBON,               // given on Thursdays to the first slot in the party
	MON_PARAM_SINNOH_RELAX_RIBBON,                  // given on Fridays to the first slot in the party
	MON_PARAM_SINNOH_SNOOZE_RIBBON,                 // given on Saturdays to the first slot in the party
	MON_PARAM_SINNOH_SMILE_RIBBON,                  // given on Sundays to the first slot in the party
	MON_PARAM_SINNOH_GORGEOUS_RIBBON,               // buy for $10,000
	MON_PARAM_SINNOH_ROUAL_RIBBON,                  // buy for $100,000
	MON_PARAM_SINNOH_GORGEOUS_ROYAL_RIBBON,         // buy for $999,999
	MON_PARAM_SINNOH_FOOTPRINT_RIBBON,              // maximum friendship
	MON_PARAM_SINNOH_RECORD_RIBBON,                 // unobtainable
	MON_PARAM_SINNOH_HISTORY_RIBBON,                // unobtainable; Event Ribbon in gen5
	MON_PARAM_SINNOH_LEGEND_RIBBON,                 // defeat Red at Mt. Silver
	MON_PARAM_SINNOH_RED_RIBBON,                    // unobtainable; World Champion Ribbon in gen5
	MON_PARAM_SINNOH_GREEN_RIBBON,                  // unobtainable; Birthday Ribbon in gen5
	MON_PARAM_SINNOH_BLUE_RIBBON,                   // unobtainable; Special Ribbon in gen5
	MON_PARAM_SINNOH_SOUVENIR_RIBBON,               // unobtainable; Festival Ribbon in gen5
	MON_PARAM_SINNOH_CARNIVAL_RIBBON,               // unobtainable; Wishing Ribbon in gen5
    MON_PARAM_SINNOH_CLASSIC_RIBBON,                // obtain the mon via Mystery Gift
    MON_PARAM_SINNOH_PREMIER_RIBBON,                // obtain an Event Mew
	MON_PARAM_SINNOH_PADDING_RIBBONS,               // leftover space in the bitfield

    // BoxPokemon Block B data
	MON_PARAM_MOVE_1,   // move IDs
	MON_PARAM_MOVE_2,
	MON_PARAM_MOVE_3,
	MON_PARAM_MOVE_4,

	MON_PARAM_PP_FOR_MOVE_1,                    // current PP for each move
	MON_PARAM_PP_FOR_MOVE_2,
	MON_PARAM_PP_FOR_MOVE_3,
	MON_PARAM_PP_FOR_MOVE_4,

	MON_PARAM_NUM_PP_UPS_FOR_MOVE_1,            // number of PP Ups applied to each move
	MON_PARAM_NUM_PP_UPS_FOR_MOVE_2,
	MON_PARAM_NUM_PP_UPS_FOR_MOVE_3,
	MON_PARAM_NUM_PP_UPS_FOR_MOVE_4,

	MON_PARAM_MAX_PP_FOR_MOVE_1,                // maximum PP for each move
	MON_PARAM_MAX_PP_FOR_MOVE_2,
	MON_PARAM_MAX_PP_FOR_MOVE_3,
	MON_PARAM_MAX_PP_FOR_MOVE_4,

	MON_PARAM_HP_IV,                            // IVs
    MON_PARAM_ATTACK_IV,
    MON_PARAM_DEFENSE_IV,
    MON_PARAM_SPEED_IV,
    MON_PARAM_SPATTACK_IV,
    MON_PARAM_SPDEFENSE_IV,

	MON_PARAM_IS_EGG,
	MON_PARAM_IS_NICKNAMED,

	MON_PARAM_HOENN_COOL_RIBBON,                // win a Hoenn Cool contest
	MON_PARAM_HOENN_COOL_RIBBON_SUPER,          // win a Hoenn Cool Super Rank contest
	MON_PARAM_HOENN_COOL_RIBBON_HYPER,          // win a Hoenn Cool Hyper Rank contest
	MON_PARAM_HOENN_COOL_RIBBON_MASTER,         // win a Hoenn Cool Master Rank contest
	MON_PARAM_HOENN_BEAUTY_RIBBON,              // ... etc.
	MON_PARAM_HOENN_BEAUTY_RIBBON_SUPER,
	MON_PARAM_HOENN_BEAUTY_RIBBON_HYPER,
	MON_PARAM_HOENN_BEAUTY_RIBBON_MASTER,
	MON_PARAM_HOENN_CUTE_RIBBON,
	MON_PARAM_HOENN_CUTE_RIBBON_SUPER,
	MON_PARAM_HOENN_CUTE_RIBBON_HYPER,
	MON_PARAM_HOENN_CUTE_RIBBON_MASTER,
	MON_PARAM_HOENN_SMART_RIBBON,
	MON_PARAM_HOENN_SMART_RIBBON_SUPER,
	MON_PARAM_HOENN_SMART_RIBBON_HYPER,
	MON_PARAM_HOENN_SMART_RIBBON_MASTER,
	MON_PARAM_HOENN_TOUGH_RIBBON,
	MON_PARAM_HOENN_TOUGH_RIBBON_SUPER,
	MON_PARAM_HOENN_TOUGH_RIBBON_HYPER,
	MON_PARAM_HOENN_TOUGH_RIBBON_MASTER,
	MON_PARAM_HOENN_CHAMPION_RIBBON,            // enter a gen3 league hall of fame (Hoenn, Kanto)
	MON_PARAM_HOENN_BATTLE_TOWER_WINNER,        // clear level 50 of the Hoenn Battle Tower
	MON_PARAM_HOENN_BATTLE_TOWER_VICTORY,       // clear level 100 of the Hoenn Battle Tower
	MON_PARAM_HOENN_ARTIST_RIBBON,              // win a Master Rank Hoenn contest with a high score and have the Pokemon's portrait painted
	MON_PARAM_HOENN_EFFORT_RIBBON,              // have 510 total EVs
	MON_PARAM_HOENN_MARINE_RIBBON,              // unobtainable; Battle Champion Ribbon in gen5
	MON_PARAM_HOENN_LAND_RIBBON,                // unobtainable; Regional Champion Ribbon in gen5
	MON_PARAM_HOENN_SKY_RIBBON,                 // unobtainable; National Champion Ribbon in gen5
	MON_PARAM_HOENN_COUNTRY_RIBBON,             // win a Pokemon Festa in 2004 or 2005
	MON_PARAM_HOENN_NATIONAL_RIBBON,            // purify a Shadow Pokemon (Colosseum)
	MON_PARAM_HOENN_EARTH_RIBBON,               // win 100 consecutive times at Mt. Battle (Colosseum)
	MON_PARAM_HOENN_WORLD_RIBBON,               // win a Pokemon Festa in 2004 or 2005

	MON_PARAM_IS_EVENT_DISTRIBUTED,
	MON_PARAM_GENDER,
	MON_PARAM_FORM_NUMBER,
	MON_PARAM_DUMMY_BLOCK_B_1,
	MON_PARAM_DUMMY_BLOCK_B_2,
	MON_PARAM_NEW_CATCH_LOCATION,
	MON_PARAM_NEW_HATCH_LOCATION,

    // BoxPokemon Block C data
    MON_PARAM_NICKNAME,
    MON_PARAM_NICKNAME_AS_CHARS_WITH_FLAG,
    MON_PARAM_NICKNAME_AS_STRBUF,
    MON_PARAM_NICKNAME_AS_STRBUF_WITH_FLAG,
	MON_PARAM_ORIGIN_COUNTRY_CODE,
	MON_PARAM_ORIGIN_GAME,

	MON_PARAM_SINNOH_COOL_RIBBON,               // win a Sinnoh Cool Super Contest
	MON_PARAM_SINNOH_COOL_RIBBON_GREAT,         // win a Sinnoh Cool Great Rank Super Contest
	MON_PARAM_SINNOH_COOL_RIBBON_ULTRA,         // win a Sinnoh Cool Ultra Rank Super Contest
	MON_PARAM_SINNOH_COOL_RIBBON_MASTER,        // win a Sinnoh Cool Master Rank Super Contest
	MON_PARAM_SINNOH_BEAUTY_RIBBON,             // ... etc.
	MON_PARAM_SINNOH_BEAUTY_RIBBON_GREAT,
	MON_PARAM_SINNOH_BEAUTY_RIBBON_ULTRA,
	MON_PARAM_SINNOH_BEAUTY_RIBBON_MASTER,
	MON_PARAM_SINNOH_CUTE_RIBBON,
	MON_PARAM_SINNOH_CUTE_RIBBON_GREAT,
	MON_PARAM_SINNOH_CUTE_RIBBON_ULTRA,
	MON_PARAM_SINNOH_CUTE_RIBBON_MASTER,
	MON_PARAM_SINNOH_SMART_RIBBON,
	MON_PARAM_SINNOH_SMART_RIBBON_GREAT,
	MON_PARAM_SINNOH_SMART_RIBBON_ULTRA,
	MON_PARAM_SINNOH_SMART_RIBBON_MASTER,
	MON_PARAM_SINNOH_TOUGH_RIBBON,
	MON_PARAM_SINNOH_TOUGH_RIBBON_GREAT,
	MON_PARAM_SINNOH_TOUGH_RIBBON_ULTRA,
	MON_PARAM_SINNOH_TOUGH_RIBBON_MASTER,
	MON_PARAM_SINNOH_PADDING_CONTEST_RIBBONS,   // leftover space in the bitfield

    // BoxPokemon Block D data
    MON_PARAM_OT_NAME,
    MON_PARAM_OT_NAME_AS_STRING,

    MON_PARAM_CAUGHT_YEAR,
    MON_PARAM_CAUGHT_MONTH,
    MON_PARAM_CAUGHT_DAY,
    MON_PARAM_BIRTH_YEAR,
    MON_PARAM_BIRTH_MONTH,
    MON_PARAM_BIRTH_DAY,

    MON_PARAM_CAUGHT_LOCATION,
    MON_PARAM_BIRTH_LOCATION,

	MON_PARAM_POKERUS,
	MON_PARAM_POKEBALL,
	MON_PARAM_MET_LEVEL,
	MON_PARAM_OT_GENDER,
    MON_PARAM_ENCOUNTER_TYPE,
    MON_PARAM_DUMMY_BLOCK_D,

    // PartyPokemon data
    MON_PARAM_CONDITION,
    MON_PARAM_LEVEL,
    MON_PARAM_CUSTOM_BALL_ID,
    MON_PARAM_CURRENT_HP,
    MON_PARAM_MAX_HP,
    MON_PARAM_ATTACK,
    MON_PARAM_DEFENSE,
    MON_PARAM_SPEED,
    MON_PARAM_SPATTACK,
    MON_PARAM_SPDEFENSE,
    MON_PARAM_MAIL_DATA,
    MON_PARAM_CUSTOM_BALLS,

    MON_PARAM_PARTYPOKEMON_MAX,

    // Extra data param definitions
	MON_PARAM_DOES_SPECIES_EXIST,               // ?
	MON_PARAM_MAYBE_EGG,                        // returns the bad egg flag if flipped, else the value of the egg flag

    MON_PARAM_SPECIES_OR_EGG,                   // returns the species number, or the egg species (if this is an egg)

	MON_PARAM_ALL_IVS,                          // returns the full 30-bit structure of a mon's IVs
	MON_PARAM_NIDORAN_NICKNAME,                 // special check for Nidoran nicknames (because they are special boys and girls)

	MON_PARAM_TYPE1,                            // gets type 1 for a mon from the BaseStats struct (special case: Arceus)
	MON_PARAM_TYPE2,                            // gets type 2 for a mon from the BaseStats struct (special case: Arceus)

	MON_PARAM_DEFAULT_NAME,                     // gets the default name for a given species

	MON_PARAM_END,
};

enum PersonalNARCField {
    PERSONAL_BASE_HP = 0,
    PERSONAL_BASE_ATTACK,
    PERSONAL_BASE_DEFENSE,
    PERSONAL_BASE_SPEED,
    PERSONAL_BASE_SP_ATTACK,
    PERSONAL_BASE_SP_DEFENSE,
    PERSONAL_TYPE_1,
    PERSONAL_TYPE_2,
    PERSONAL_CATCH_RATE,
    PERSONAL_EXP_YIELD,
    PERSONAL_EV_YIELD_HP,
    PERSONAL_EV_YIELD_ATTACK,
    PERSONAL_EV_YIELD_DEFENSE,
    PERSONAL_EV_YIELD_SPEED,
    PERSONAL_EV_YIELD_SP_ATTACK,
    PERSONAL_EV_YIELD_SP_DEFENSE,
    PERSONAL_ITEM_1,
    PERSONAL_ITEM_2,
    PERSONAL_GENDER_RATIO,
    PERSONAL_EGG_CYCLES,
    PERSONAL_BASE_FRIENDSHIP,
    PERSONAL_EXP_GROUP,
    PERSONAL_EGG_GROUP_1,
    PERSONAL_EGG_GROUP_2,
    PERSONAL_ABILITY_1,
    PERSONAL_ABILITY_2,
    PERSONAL_RUN_CHANCE,
    PERSONAL_BODY_COLOR,
    PERSONAL_FLIP,
    PERSONAL_TM_ARRAY_1,
    PERSONAL_TM_ARRAY_2,
    PERSONAL_TM_ARRAY_3,
    PERSONAL_TM_ARRAY_4,
};

enum PokemonNature {
    NATURE_HARDY,
    NATURE_LONELY,
    NATURE_BRAVE,
    NATURE_ADAMANT,
    NATURE_NAUGHTY,
    NATURE_BOLD,
    NATURE_DOCILE,
    NATURE_RELAXED,
    NATURE_IMPISH,
    NATURE_LAX,
    NATURE_TIMID,
    NATURE_HASTY,
    NATURE_SERIOUS,
    NATURE_JOLLY,
    NATURE_NAIVE,
    NATURE_MODEST,
    NATURE_MILD,
    NATURE_QUIET,
    NATURE_BASHFUL,
    NATURE_RASH,
    NATURE_CALM,
    NATURE_GENTLE,
    NATURE_SASSY,
    NATURE_CAREFUL,
    NATURE_QUIRKY,
};

// ===== BASE GAME CODE FUNCTIONS (UNMODIFIED) ===== //

/**
 * @brief Get data from the BoxPokemon structure.
 * 
 * Original Function: [`GetBoxPkmnData @ 0x02074570` (ARM9)](https://github.com/JimB16/PokePlat/blob/6d4ad87550eeb40079ede6dcf5dddec5873976e4/source/arm9_pkmndata.s#L1376)
 * 
 * @param[in]  boxMon   The BoxPokemon structure from which to pull data.
 * @param[in]  field    Field ID of the data to be pulled from the structure.
 * @param[out] buf      Buffer output, for array output.
 * @return              Result data.
 */
u32  __attribute__((long_call)) BoxPokemon_Get(struct BoxPokemon *boxMon, int field, void *buf);

/**
 * @brief Initializes a new Pokemon structure.
 * 
 * @param[in,out]   pokemon
 * @param[in]       species
 * @param[in]       level
 * @param[in]       ivs         Value to set for all IVs.
 * @param[in]       rndSetFlag  If 0, will ignore any value in rnd and generate a new random value.
 * @param[in]       rnd         Pre-set random value. Used for computing PID (and, thus, gender, nature, etc.).
 * @param[in]       idFlag      If 0, generate new ID for the original trainer. If 1, use value from id. If 2, force the mon to not be shiny.
 * @param[in]       id          Pre-set original trainer ID.
 */
void __attribute__((long_call)) Pokemon_Init(struct Pokemon *pokemon, int species, int level, int ivs, int rndSetFlag, u32 rnd, int idFlag, u32 id);

/**
 * @brief Get data from the Pokemon structure.
 * 
 * Original Function: [`GetPkmnData @ 0x02074470` (ARM9)](https://github.com/JimB16/PokePlat/blob/ccbdf7ea8b08f23d3adcb6baa7d1f2b8dc24bbc1/source/arm9_pkmndata.s#L1198)
 * 
 * @param[in]  pokemon  The Pokemon structure from which to pull data.
 * @param[in]  field    Field ID of the data to be pulled from the structure.
 * @param[out] buf      Buffer output, for array output.
 * @return              Result data.
 */
u32  __attribute__((long_call)) Pokemon_Get(struct Pokemon *pokemon, int field, void *buf);

/**
 * @brief Set data in the Pokemon structure.
 * 
 * @param[in,out]   pokemon
 * @param[in]       field   Field ID of the data to be set. See enum PokemonDataField.
 * @param[in]       buf     Pointer to new data to assign.
 */
void __attribute__((long_call)) Pokemon_Set(struct Pokemon *pokemon, int field, void *buf);

/**
 * @brief Sets the move ID in a particular slot for a Pokemon.
 * 
 * @param[in,out]   pokemon
 * @param[in]       moveID  ID of the move to be set.
 * @param[in]       slot    Slot to set the move into, 0-indexed.
 */
void __attribute__((long_call)) Pokemon_SetMoveSlot(struct Pokemon *pokemon, u16 moveID, u8 slot);

/**
 * @brief Recalculates computed attributes for a Pokemon (e.g. stats, etc.).
 * 
 * @param[in,out]   pokemon
 */
void __attribute__((long_call)) Pokemon_Recalc(struct Pokemon *pokemon);

/**
 * @brief Checks if a given Pokemon species + form can learn the move in a given TM.
 * 
 * @param[in]   species
 * @param[in]   form
 * @param[in]   tmID    ID of the TM in question. 0 is TM01. 92 is HM01.
 * @return              TRUE if the Pokemon can learn the TM, FALSE otherwise.
 */
BOOL __attribute__((long_call)) Pokemon_CanLearnTM(u16 species, u16 form, u8 tmID);

/**
 * @brief Allocate and return a new Pokemon struct.
 * 
 * @param[in]   heapID  ID of the heap which will own the struct.
 * @return              An allocated Pokemon struct.
 */
struct Pokemon* __attribute__((long_call)) Pokemon_Malloc(u32 heapID);

/**
 * @brief Assign a ball seal to a Pokemon.
 * 
 * @param[in]       ballSeal    ID of the ball seal.
 * @param[in,out]   pokemon
 * @param[in]       heapID      Heap for loading the ball seal archive.
 * @return                      TRUE if the ball seal is valid, FALSE otherwise.
 */
BOOL __attribute__((long_call)) Pokemon_AssignBallSeal(int ballSeal, struct Pokemon *pokemon, int heapID);

/**
 * @brief Get a data value for a species from the base stats archive.
 * 
 * @param[in]   species     Species ID to be retrieved. This should be the "true" species ID (see: Form_CalcTrueSpecies).
 * @param[in]   field       ID of the data field to retrieve.
 * @return                  Requested data value.
 */
u32  __attribute__((long_call)) Pokemon_GetBaseStats(int species, int field);

/**
 * @brief Calculates the "true" species of a given species + form combination.
 * 
 * This is used to permute forms on Pokemon with those that have separate entries
 * in the base stats archive, i.e.:
 *  - Deoxys (Attack, Defense, Speed forms)
 *  - Wormadam (Sandy, Trash forms)
 *  - Giratina (Origin form)
 *  - Shaymin (Sky form)
 *  - Rotom (Heat, Wash, Frost, Fan, Mow forms)
 * 
 * @param[in]   species     Species ID of the base form
 * @param[in]   form        ID of the permuted form (0 being the base form)
 * @return                  The "true" species ID
 */
int  __attribute__((long_call)) Form_CalcTrueSpecies(int species, int form);

#endif // __POKEMON_H