#include <kernel/qemu.h>
#include <libk/string.h>
#include <libk/stdarg.h>
#include <arch/arch.h>

// If logger is on or off
int is_on = 0;

// Checks if 0xe9 hack is supported
void __dinit() {
  arch_outb(0xE9, 0xE9);
  // if 0xE9 is returned, then e9 hack is supported
  // else we are on real hardware
  if(arch_inb(0xE9) == 0xE9) {
    is_on = 1;
  }
}

void qemu_putc(char c) {
  arch_outb(0xE9, c);
}

void qemu_puts(char* str) {
  for(int l = 0; l < strlen(str); l++) {
    qemu_putc(str[l]);
  }
}

void __dlog(char* modname, char* fmt, ...) {\
  if(!is_on) {
    return; // Logging isn't supported, waste of time
  }
  char buf[200];
  char bufb[300];
  va_list mk;
  va_start(mk, fmt);
  vsprintf(buf, fmt, mk);
  va_end(mk);
  sprintf(bufb, "[%s] - %s\n", modname, buf);
  qemu_puts(bufb);
}

