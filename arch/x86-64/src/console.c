#include <arch/console.h>
#include <arch/arch.h>
#include <libk/memory.h>
#include <arch/bootboot.h>
#define INCBIN_PREFIX
#include <arch/incbin.h>

extern u8 fb;
extern BOOTBOOT bootboot;

INCBIN(font, "../arch/x86-64/src/font.psf");

int kx = 0;

void __putch(char *s) {
  psf2_t *font = (psf2_t*)&fontData;
  int x, y, line, mask, offs = 0;
  int bpl = (font->width + 7) / 8;
  u8 *glyph = (u8*)&fontData + font->headersize +
  (*s>0&&*s<font->numglyph?*s:0)*font->bytesperglyph;
  offs = (kx * (font->width+1) * 4);
  for(y=0;y<font->height;y++) {
    line=offs; mask=1<<(font->width-1);
    for(x=0;x<font->width;x++) {
      *((u32*)((u64)&fb+line))=((int)*glyph) & (mask)?0xFFFFFF:0;
      mask>>=1; line+=4;
    }
    *((u32*)((u64)&fb+line))=0; glyph+=bpl; offs+=bootboot.fb_scanline;
  }
  kx++;
} 

// Not Yet Implemented!
void arch_cls() {}

void console_putch(char c) {
  __putch(&c);
}
static void console_init(void* addr, int height, int width) {
  return; // Nothing is needed!
}

tty_init arch_get_cinit() {
  return console_init;
}
tty_putch arch_get_cputch() {
  return console_putch;
}