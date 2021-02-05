#include <kernel/qemu.h>
#include <libk/string.h>
#include <libk/stdarg.h>
#include <arch/arch.h>

void qemu_putc(char c) {
  arch_outb(0xE9, c);
}

void qemu_puts(char* str) {
  for(int l = 0; l < strlen(str); l++) {
    qemu_putc(str[l]);
  }
}

void __dlog(char* modname, char* fmt, ...) {
  char buf[200];
  char bufb[300];
  va_list mk;
  va_start(mk, fmt);
  vsprintf(buf, fmt, mk);
  va_end(mk);
  sprintf(bufb, "[%s] - %s\n", modname, buf);
  qemu_puts(bufb);
}

