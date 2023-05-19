#ifndef __SYS_H
#define __SYS_H

#include "typedefs.h"

u32  __attribute__((long_call)) RNG_Seed(void);
void __attribute__((long_call)) RNG_SetSeed(u32 seed);
u16  __attribute__((long_call)) RNG_Get(void);

void* __attribute__((long_call)) Malloc(u32 heapID, u32 size);
void  __attribute__((long_call)) Free(void *memBlock);

#endif // SYS_H