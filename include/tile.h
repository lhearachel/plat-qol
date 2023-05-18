#ifndef __TILE_H
#define __TILE_H

#include "typedefs.h"

BOOL __attribute__((long_call)) Tile_IsPC(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsSmallBookshelf_01(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsSmallBookshelf_02(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsBookshelf_01(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsBookshelf_02(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsTrashcan(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsShopBookshelf_01(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsShopBookshelf_02(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsShopBookshelf_03(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsWaterfall(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsMap(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsBumpPost(u8 nextTile);
BOOL __attribute__((long_call)) Tile_IsTV(u8 nextTile);

#endif