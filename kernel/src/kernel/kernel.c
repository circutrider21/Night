#include <kernel.h>
#include <drivers/display/vbe.h>
#include <drivers/display/legcon.h>
#include <arch/handover.h>
#include <arch/arch.h>

void kmain(handover_t* hd) {
  if(vbe_init(hd) == 1) {
    vbe_puts("Hello, World!");
  } else if (lcon_init(hd) == 1) {
    lcon_puts("Hello, World!");
  }
  arch_halt();
}