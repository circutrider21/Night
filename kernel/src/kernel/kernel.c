#include <kernel.h>
#include <drivers/display/vbe.h>
#include <drivers/display/legcon.h>
#define MODULE_NAME "KMAIN"
#include <kernel/logger.h>
#include <arch/handover.h>
#include <arch/arch.h>

void kmain(handover_t* hd) {
  DLOG("Hello from kernel!");
  if(vbe_init(hd) == 1) {
    DLOG("System Supports VBE!");
    vbe_puts("Hello, World!");
  } else if (lcon_init(hd) == 1) {
    DLOG("System Supports CGA Mode!");
    lcon_puts("Hello, World!");
  }
  __asm volatile ("int $10");
  arch_halt();
}
