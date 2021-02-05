#include <arch/console.h>
#include <arch/arch.h>
#include <libk/memory.h>

u16 *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;
int _width, _height = 0;


static void* con_memcpy(void *dest, const void *src, size_t count) {
  const char *sp = (const char *)src;
  char *dp = (char *)dest;
  for (; count != 0; count--) *dp++ = *sp++;
  return dest;
}

static int con_memcmp(u8* uno, u8* dos, int num) {
  for(int k = 0; k < num; k++) {
    if(uno[k] != dos[k]) {
      return 1;
    }
  }

  return 0;
}

static void *con_memset(void *dest, char val, size_t count) {
  char *temp = (char *)dest;
  for (; count != 0; count--) *temp++ = val;
  return dest;
}

static u16 *con_memsetw(u16 *dest, u16 val, size_t count) {
  u16 *temp = (u16 *)dest;
  for (; count != 0; count--) *temp++ = val;
  return dest;
}

static void scroll(void) {
  u32 blank, temp;

  blank = 0x20 | (attrib << 8);

  if (csr_y >= _height) {
    temp = csr_y - _height + 1;
    con_memcpy(textmemptr, textmemptr + temp * _width, (_height - temp) * _width * 2);

    con_memsetw(textmemptr + (_height - temp) * _width, blank, _width);
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

void arch_cls() {
  u32 blank;
  int i;

  blank = 0x20 | (attrib << 8);
  for (i = 0; i < _height; i++) con_memsetw(textmemptr + i * _width, blank, _width);

  /* Update out virtual cursor, and then move the
   *  hardware cursor */
  csr_x = 0;
  csr_y = 0;
  move_csr();
}

void console_putch(char c) {
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

static void console_init(void* addr, int height, int width) {
  textmemptr = (u16*)addr;
  _width = width;
  _height = height;
  arch_cls();
}

tty_init arch_get_cinit() {
  return console_init;
}
tty_putch arch_get_cputch() {
  return console_putch;
}