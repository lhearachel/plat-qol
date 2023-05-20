#include "config.h"

#ifdef BUGFIX_BOSS_DOUBLES_MUSIC

#include "battle.h"

enum SpecialEffects {
    SPFX_ROARK,
    SPFX_GARDENIA,
    SPFX_WAKE,
    SPFX_MAYLENE,
    SPFX_FANTINA,
    SPFX_CANDICE,
    SPFX_BYRON,
    SPFX_VOLKNER,
    SPFX_AARON,
    SPFX_BERTHA,
    SPFX_FLINT,
    SPFX_LUCIAN,
    SPFX_CYNTHIA,
    SPFX_RIVAL,                 // Barry

    SPFX_SHAYMIN,
    SPFX_DIALGA_PALKIA,
    SPFX_UXIE_AZELF,
    SPFX_MESPRIT,
    SPFX_ARCEUS,
    SPFX_OTHER_LEGENDS,         // Regigigas, Heatran, Darkrai
    SPFX_CRESSELIA,             // Cresselia
    SFPX_ROAMING_BIRDS,         // Articuno, Moltres, Zapdos
    SPFX_GIRATINA,
    SPFX_REGI_GOLEMS,           // Regirock, Regice, Registeel

    SPFX_GALACTIC_GRUNT,
    SPFX_GALACTIC_COMMANDER,    // Mars, Jupiter, Saturn
    SPFX_CYRUS,

    SPFX_TOWER_TRAINER,
    SPFX_LINK_BATTLE,
    SPFX_DOUBLE_BATTLE,
    SPFX_DOUBLE_WILD_BATTLE,

    SPFX_FRONTIER_BRAIN,

    SPFX_TAG_BATTLE_BOSS,       // Specifically, tag with Barry vs Volkner and Flint

    SPFX_NORMAL_TRAINER,
    SPFX_NORMAL_WILD,

    SPFX_MAX
};

static inline BOOL IsGalactic(u32 effectsIdx)
{
    return (
        (effectsIdx == SPFX_GALACTIC_GRUNT)
            || (effectsIdx == SPFX_GALACTIC_COMMANDER)
            || (effectsIdx == SPFX_CYRUS)
    );
}

static inline BOOL IsSpecialTrainer(u32 effectsIdx)
{
    return (
        // Gym Leaders, Elite Four, Cynthia, Rival
        ((effectsIdx <= SPFX_RIVAL))
            // Team Galactic
            || IsGalactic(effectsIdx)
            // Frontier Brains
            || (effectsIdx == SPFX_FRONTIER_BRAIN)
    );
}

u32 FieldEncounter_GetSpecialEffects(const struct BattleParams *battleParams)
{
    u32 fightType = battleParams->fightType;
    u32 effectsIdx;

    if (fightType & FIGHT_TYPE_TRAINER) {
        effectsIdx = FieldEncounter_GetTrainerSpecialEffects(battleParams->trainerData[CLIENT_ENEMY].trainerClass);

        if (fightType & FIGHT_TYPE_TOWER) {
            if (effectsIdx == SPFX_FRONTIER_BRAIN) {
                return effectsIdx;
            }

            if (effectsIdx == FIGHT_TYPE_DOUBLES) {
                return SPFX_DOUBLE_BATTLE;
            }

            return SPFX_TOWER_TRAINER;
        }

        if (fightType & FIGHT_TYPE_DOUBLES) {
            if (IsSpecialTrainer(effectsIdx)) {
                if (fightType & FIGHT_TYPE_AI_TWO_ENEMIES) {
                    return SPFX_TAG_BATTLE_BOSS;
                }

                return effectsIdx;
            }

            return SPFX_DOUBLE_BATTLE;
        }

        if (fightType & FIGHT_TYPE_LINK) {
            return SPFX_LINK_BATTLE;
        }

        return effectsIdx;
    }

    // Everything after this is related to wild Pokemon
    effectsIdx = FieldEncounter_GetPokemonSpecialEffects(battleParams->party[CLIENT_ENEMY], battleParams->zoneID);

    if (effectsIdx < SPFX_NORMAL_WILD) {
        return effectsIdx;
    }

    if (fightType & FIGHT_TYPE_DOUBLES) {
        return SPFX_DOUBLE_WILD_BATTLE;
    }

    return effectsIdx;
}

#endif