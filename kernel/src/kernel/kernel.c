#include <kernel.h>
#include <drivers/tty.h>
#include <arch/console.h>
#include <arch/handover.h>
#include <arch/arch.h>

void kmain(handover_t* hd) {
  init_tty(hd->framebuffer, hd->height, hd->width);
  tty_set_callbacks(arch_get_cinit(), arch_get_cputch());
  tty_puts("Hello, World!");
  arch_halt();
}