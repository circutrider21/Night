#ifndef NIGHT_TTY_H
#define NIGHT_TTY_H

#include <libk/types.h>

typedef void (*tty_putch)(char);
typedef void (*tty_init)(void*, int, int);

void init_tty(void* addr, int height, int width);
void tty_set_callbacks(tty_init ti, tty_putch tp);

void tty_puts(char* str);
void tty_put(char p);

#endif // NIGHT_TTY_H