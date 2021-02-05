#ifndef LIBK_MEMORY_H
#define LIBK_MEMORY_H

#include "types.h"

void outb(u16 _port, u8 _data);
u8 inb(u16 _port);
u16 *memsetw(u16 *dest, u16 val, size_t count);
void *memset(void *dest, char val, size_t count);
int memcmp(u8* uno, u8* dos, int num);
void *memcpy(void *dest, const void *src, size_t count);

#endif