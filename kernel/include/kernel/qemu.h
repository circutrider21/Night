#ifndef NIGHT_QEMU_H
#define NIGHT_QEMU_H

#include <libk/stdarg.h>

#define DLOG(k, ...) __dlog(MODULE_NAME, k, #__VA_ARGS__);

void __dlog(char* modname, char* fmt, ...);
void qemu_putc(char c);
void qemu_puts(char* str);

#endif // NIGHT_QEMU_H