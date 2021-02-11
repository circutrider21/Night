#include <drivers/display/legcon.h>
#include <arch/arch.h>
#include <libk/memory.h>

u16 *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;
int _width, _height = 0;

static void scroll(void) {
  u32 blank, temp;

  blank = 0x20 | (attrib << 8);

  if (csr_y >= _height) {
    temp = csr_y - _height + 1;
    memcpy(textmemptr, textmemptr + temp * _width, (_height - temp) * _width * 2);

    memsetw(textmemptr + (_height - temp) * _width, blank, _width);
    csr_y = _height - 1;
  }
}

static void move_csr(void) {
  u32 temp;

  /* The equation for finding the index in a linear
   *  chunk of memory can be represented by:
   *  Index = [(y * width) + x] */
  temp = csr_y * _width + csr_x;

  arch_outb(0x3D4, 14);
  arch_outb(0x3D5, temp >> 8);
  arch_outb(0x3D4, 15);
  arch_outb(0x3D5, temp);
}

void lcon_clear() {
  u32 blank;
  int i;

  blank = 0x20 | (attrib << 8);
  for (i = 0; i < _height; i++) memsetw(textmemptr + i * _width, blank, _width);

  /* Update out virtual cursor, and then move the
   *  hardware cursor */
  csr_x = 0;
  csr_y = 0;
  move_csr();
}

void lcon_putc(char c) {
  u16 *loc;
  u32 att = attrib << 8;

  /* Handle a backspace, by moving the cursor back one space */
  if (c == 0x08) {
    if (csr_x != 0) csr_x--;
    loc = textmemptr + (csr_y * _width + csr_x);
    *loc = ' ' | att;
  }
  else if (c == 0x09) {
    csr_x = (csr_x + 8) & ~(8 - 1);
  }
  else if (c == '\r') {
    csr_x = 0;
  }
  else if (c == '\n') {
    csr_x = 0;
    csr_y++;
  }
  else if (c >= ' ') {
    loc = textmemptr + (csr_y * _width + csr_x);
    *loc = c | att;
    csr_x++;
  }
  if (csr_x >= _width) {
    csr_x = 0;
    csr_y++;
  }

  scroll();
  move_csr();
}

void lcon_puts(char* s) {
    for(int l = 0; l < strlen(s); l++) {
        lcon_putc(s[l]);
    }
}

int lcon_init(handover_t* h) {
  if(h->pitch != 0) {
      return 0;
  } else {
    textmemptr = (u16*)h->framebuffer;
    _width = h->width;
    _height = h->height;
    lcon_clear();
    return 1;
  }
}

void lcon_setcolor(u8 fg, u8 bg) {
    attrib = (bg << 4) | (fg & 0x0F);
}