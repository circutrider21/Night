#include <arch/pic_8259.h>
#define MODULE_NAME "PIC_8259"
#include <kernel/logger.h>

struct __pic {
  u8 masks[2];
};

static struct __pic p = {0};

void init_pic() {
  DLOG("Initializing PIC...");
  // Save original masks before proceding
  p.masks[0] = arch_inb(PIC0_DATA);
  p.masks[1] = arch_inb(PIC1_DATA);

  DLOG("PIC0 Mask = %x", p.masks[0]);
  DLOG("PIC1 Mask = %x", p.masks[1]);

  // Start init process
  arch_outb(PIC0_CMD, INIT_CMD);
  IO_WAIT();
  arch_outb(PIC1_CMD, INIT_CMD);
  IO_WAIT();

  // Set PIC Offset
  arch_outb(PIC0_DATA, 32);
  IO_WAIT();
  arch_outb(PIC1_DATA, 32 + 8);
  IO_WAIT();

  // Enable PIC Chaining
  arch_outb(PIC0_DATA, 4);
  IO_WAIT();
  arch_outb(PIC1_DATA, 2);
  IO_WAIT();

  // Set Operating mode (8086 Mode)
  arch_outb(PIC0_DATA, 0x01);
  IO_WAIT();
  arch_outb(PIC1_DATA, 0x01);
  IO_WAIT();

  // Restore Masks
  arch_outb(PIC0_DATA, p.masks[0]);
  arch_outb(PIC1_DATA, p.masks[1]);

  // Complete!
  DLOG("PIC Ready!");
  __asm volatile ("sti");
}