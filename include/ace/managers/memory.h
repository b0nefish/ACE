/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _ACE_MANAGERS_MEMORY_H_
#define _ACE_MANAGERS_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef AMIGA
#include <exec/memory.h>      // MEMF_CLEAR etc
#else
#define MEMF_CHIP    0
#define MEMF_FAST    1
#define MEMF_CLEAR   2
#define MEMF_PUBLIC  4
#define MEMF_LARGEST 8
#endif // AMIGA

#include <ace/types.h>

/* Types */

/* Globals */

/* Functions */

/**
 * @brief Checks whether memory pointer is in CHIP or FAST mem.
 *
 * @param pMem Pointer to memory to be checked.
 * @return MEMF_CHIP or MEMF_FAST.
 */
UBYTE memType(const void *pMem);

void _memCreate(void);
void _memEntryAdd(void *pAddr, ULONG ulSize, UWORD uwLine, char *szFile);
void _memEntryDelete(void *pAddr, ULONG ulSize, UWORD uwLine, char *szFile);
void _memDestroy(void);

void *_memAllocDbg(ULONG ulSize, ULONG ulFlags, UWORD uwLine, char *szFile);
void _memFreeDbg(void *pMem, ULONG ulSize, UWORD uwLine, char *szFile);
void *_memAllocRls(ULONG ulSize, ULONG ulFlags);
void _memFreeRls(void *pMem, ULONG ulSize);

void _memCheckTrash(void *pMem, UWORD uwLine, char *szFile);

/**
 * Macros for enabling or disabling logging
 */

#ifdef ACE_DEBUG
# define memAlloc(ulSize, ulFlags) _memAllocDbg(ulSize, ulFlags, __LINE__, __FILE__)
# define memFree(pMem, ulSize) _memFreeDbg(pMem, ulSize, __LINE__, __FILE__)
# define memCreate() _memCreate()
# define memDestroy() _memDestroy()
# define memEntryAdd(pAddr, ulSize) _memEntryAdd(pAddr, ulSize, __LINE__, __FILE__)
# define memEntryDelete(pAddr, ulSize) _memEntryDelete(pAddr, ulSize, __LINE__, __FILE__)
# define memCheckTrash(pAddr) _memCheckTrash(pAddr, __LINE__, __FILE__)
#else
# define memAlloc(ulSize, ulFlags) _memAllocRls(ulSize, ulFlags)
# define memFree(pMem, ulSize) _memFreeRls(pMem, ulSize)
# define memCreate()
# define memDestroy()
# define memEntryAdd(pAddr, ulSize)
# define memEntryDelete(pAddr, ulSize)
# define memCheckTrash(pAddr, ulSize)
#endif // ACE_DEBUG

// Shorthands
#define memAllocFast(ulSize) memAlloc(ulSize, MEMF_ANY)
#define memAllocChip(ulSize) memAlloc(ulSize, MEMF_CHIP)
#define memAllocFastClear(ulSize) memAlloc(ulSize, MEMF_ANY | MEMF_CLEAR)
#define memAllocChipClear(ulSize) memAlloc(ulSize, MEMF_CHIP | MEMF_CLEAR)
#define memAllocChipFlags(ulSize, ulFlags) memAlloc(ulSize, MEMF_CHIP | ulFlags)
#define memAllocFastFlags(ulSize, ulFlags) memAlloc(ulSize, MEMF_ANY |ulFlags)

#ifdef __cplusplus
}
#endif

#endif // _ACE_MANAGERS_MEMORY_H_
