/* battle.h */
FieldEncounter_GetTrainerSpecialEffects = 0x02051C20 | 1;
FieldEncounter_GetPokemonSpecialEffects = 0x02051CD0 | 1;

/* item.h */
Item_IsMail = 0x0207D2D0 | 1;
PlayerItems_HaveAtLeast = 0x0207D688 | 1;

/* party.h */
Party_GetMember = 0x0207A0FC | 1;
Party_Init = 0x0207A014 | 1;
Party_Add = 0x0207A048 | 1;

/* player.h */
Player_Form = 0x0205EB74 | 1;
Player_Direction = 0x0205EA78 | 1;
Player_CalcCurrentMapAttributes = 0x02061760 | 1;
Player_CanSurfFromHere = 0x021E0118 | 1;
Player_CanRockClimbFromHere = 0x021E0760 | 1;

/* pokemon.h */
BoxPokemon_Get = 0x02074570 | 1;
Pokemon_Init = 0x02073D80 | 1;
Pokemon_Get = 0x02074470 | 1;
Pokemon_Set = 0x02074B30 | 1;
Pokemon_SetMoveSlot = 0x02077230 | 1;
Pokemon_Recalc = 0x0207418C | 1;
Pokemon_CanLearnTM = 0x02077FE4 | 1;
Pokemon_Malloc = 0x02073C74 | 1;
Pokemon_AssignBallSeal = 0x02078AEC | 1;
Pokemon_GetBaseStats = 0x020759F0 | 1;
Form_CalcTrueSpecies = 0x02078740 | 1;

/* save.h */
SaveData_GetPlayerStatus = 0x02025E38 | 1;
SaveData_GetPlayerItems = 0x0207D990 | 1;
PlayerStatus_CheckBadge = 0x02025F34 | 1;

/* sys.h */
RNG_Seed = 0x0201D2D0 | 1;
RNG_SetSeed = 0x0201D2DC | 1;
RNG_Get = 0x0201D2E8 | 1;
Malloc = 0x02018144 | 1;
Free = 0x020181C4 | 1;

/* tile.h */
Tile_IsPC = 0x0205DBE4 | 1;
Tile_IsSmallBookshelf_01 = 0x0205DC80 | 1;
Tile_IsSmallBookshelf_02 = 0x0205DC8C | 1;
Tile_IsBookshelf_01 = 0x0205DC98 | 1;
Tile_IsBookshelf_02 = 0x0205DCA4 | 1;
Tile_IsTrashcan = 0x0205DCB0 | 1;
Tile_IsShopBookshelf_01 = 0x0205DCBC | 1;
Tile_IsShopBookshelf_02 = 0x0205DCC8 | 1;
Tile_IsShopBookshelf_03 = 0x0205DCD4 | 1;
Tile_IsWaterfall = 0x0205DDB4 | 1;
Tile_IsMap = 0x0205DBF0 | 1;
Tile_IsBumpPost = 0x0205DDC0 | 1;
Tile_IsTV = 0x0205DE84 | 1;

/* trainer.h */
Trainer_LoadParty = 0x0207939C | 1;
Trainer_Gender = 0x020793AC | 1;

/* ui/party_list.h */
PartyList_CalcMenuIDForMove = 0x02080BCC | 1;
PartyList_LoadMoveMenuString = 0x02081CAC | 1;

/* ui/summary.h */
Summary_GetPokemonData = 0x0208DD48 | 1;
Summary_NumberToString = 0x02090184 | 1;
Summary_PrintString = 0x020900D8 | 1;
Summary_PrintCurrentOverMax = 0x020901D0 | 1;

/* ui/window.h */
Window_FillWithColor = 0x0201ADA4 | 1;
Window_ToVRAM = 0x0201A9A4 | 1;

/* stragglers */
BattleTower_IsSalon = 0x0206C0D0 | 1;