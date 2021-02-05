#ifndef NIGHT_X32_ARCH_H
#define NIGHT_X32_ARCH_H

#include <libk/types.h>

u8 arch_inb(u16 _port);

void arch_outb(u16 _port, u8 _data);

void arch_halt();

#endif // NIGHT_X32_ARCH_H