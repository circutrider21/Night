#ifndef NIGHT_X64_CONSOLE_H
#define NIGHT_X64_CONSOLE_H

#include <drivers/tty.h>

tty_init arch_get_cinit();
tty_putch arch_get_cputch();
void arch_cls();

#endif // NIGHT_X64_CONSOLE_H