#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * This is a feature-flag file. It consists only of a series of defines which
 * determine how the rest of the repository will be built. You don't need to
 * worry about any of the details of allocation or linking; all of it gets
 * managed for you in the background.
 * 
 * If you want to turn off any given feature in this project, simply comment
 * out the relevant line by preceding it with "//".
 */

// Builds the detailed summary screen page with IVs, EVs, and Highlighting
// of stats affected by a Pokemon's nature.
#define DETAILED_SUMMARY_SCREEN

// Enables infinite-use TMs.
#define UNLIMITED_TMS

// Increases the HP bar drain speed in combat (~4x faster).
#define FASTER_HP_BAR_DRAIN

// Allows the use of HMs in the field so long as a Pokemon can learn it.
#define FIELD_HMS

// Maps a B button input on the Battle Command Selection screen to Run
#define MAP_B_TO_RUN_FROM_BATTLES

// Fixes a bug in vanilla Platinum that overrides the custom cut-in effects
// and music used by Gym Leaders and Elite Four members.
#define BUGFIX_BOSS_DOUBLES_MUSIC

#endif // __CONFIG_H