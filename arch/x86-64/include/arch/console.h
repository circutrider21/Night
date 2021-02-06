#ifndef NIGHT_X64_CONSOLE_H
#define NIGHT_X64_CONSOLE_H

#include <drivers/tty.h>

typedef struct {
  u32 magic;
  u32 version;
  u32 headersize;
  u32 flags;
  u32 numglyph;
  u32 bytesperglyph;
  u32 height;
  u32 width;
  u8 glyphs;
} __attribute__((packed)) psf2_t;

tty_init arch_get_cinit();
tty_putch arch_get_cputch();
void arch_cls();

#endif // NIGHT_X64_CONSOLE_H