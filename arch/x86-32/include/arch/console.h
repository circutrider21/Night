#ifndef NIGHT_X32_CONSOLE_H
#define NIGHT_X32_CONSOLE_H

#include <drivers/tty.h>

tty_init arch_get_cinit();
tty_putch arch_get_cputch();
void arch_cls();

#endif // NIGHT_X32_CONSOLE_H