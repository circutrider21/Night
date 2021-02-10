#ifndef LIBK_TYPES_H
#define LIBK_TYPES_H

typedef unsigned long long size_t;
typedef unsigned long long u64;
typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;
#define NULL ((void*)0)

#if defined(NIGHT_IS_X64)
typedef u64 addr_t; // Helps provide clarification
#else
typedef u32 addr_t;
#endif

// Makeshift Implentation of the bool type
#define bool int
#define true 1
#define false 0

#endif