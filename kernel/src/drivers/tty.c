#include <drivers/tty.h>

static void* fbuf;
static int wid;
static int hei;
static tty_putch tk;

void init_tty(void* addr, int height, int width) {
  fbuf = addr;
  wid = width;
  hei = height;
}

void tty_set_callbacks(tty_init ti, tty_putch tp) {
  tk = tp;
  ti(fbuf, hei, wid);
}

void tty_put(char p) {
  tk(p);
}

void tty_puts(char* str) {
  for(int l = 0; l < strlen(str); l++) {
    tty_put(str[l]);
  }
}