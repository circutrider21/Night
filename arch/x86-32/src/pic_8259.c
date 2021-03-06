#include <arch/pic_8259.h>
#define MODULE_NAME "PIC_8259"
#include <kernel/logger.h>
#include <arch/idt.h>

struct __pic {
  volatile u8 masks[2];
};

static void* handlers[16] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

static struct __pic p = {0};

void set_handler(u8 slot, void* hand) {
  handlers[slot] = hand;
}

static void irq_install() {
  idt_set_gate(32, (unsigned)_irq0, 0x08, 0x8E);
  idt_set_gate(33, (unsigned)_irq1, 0x08, 0x8E);
  idt_set_gate(34, (unsigned)_irq2, 0x08, 0x8E);
  idt_set_gate(35, (unsigned)_irq3, 0x08, 0x8E);
  idt_set_gate(36, (unsigned)_irq4, 0x08, 0x8E);
  idt_set_gate(37, (unsigned)_irq5, 0x08, 0x8E);
  idt_set_gate(38, (unsigned)_irq6, 0x08, 0x8E);
  idt_set_gate(39, (unsigned)_irq7, 0x08, 0x8E);

  idt_set_gate(40, (unsigned)_irq8, 0x08, 0x8E);
  idt_set_gate(41, (unsigned)_irq9, 0x08, 0x8E);
  idt_set_gate(42, (unsigned)_irq10, 0x08, 0x8E);
  idt_set_gate(43, (unsigned)_irq11, 0x08, 0x8E);
  idt_set_gate(44, (unsigned)_irq12, 0x08, 0x8E);
  idt_set_gate(45, (unsigned)_irq13, 0x08, 0x8E);
  idt_set_gate(46, (unsigned)_irq14, 0x08, 0x8E);
  idt_set_gate(47, (unsigned)_irq15, 0x08, 0x8E);
}


void handle_irq(struct regs *r) {
  arch_outb(0xE9, '!');
  /* This is a blank function pointer */
  void (*handler)(struct regs * r);

  /* Find out if we have a custom handler to run for this
   *  IRQ, and then finally, run it */
  handler = handlers[r->int_no - 32];
  if (handler) { handler(r); } // Interrupt Unknown

  /* If the IDT entry that was invoked was greater than 40
   *  (meaning IRQ8 - 15), then we need to send an EOI to
   *  the slave controller */
  if (r->int_no >= 40) { arch_outb(0xA0, 0x20); }

  /* In either case, we need to send an EOI to the master
   *  interrupt controller too */
  arch_outb(0x20, 0x20);
}

void init_pic() {
  DLOG("Initializing PIC...");
  // Setup PIC
  arch_outb(0x20, 0x11);
  arch_outb(0xA0, 0x11);
  arch_outb(0x21, 0x20);
  arch_outb(0xA1, 0x28);
  arch_outb(0x21, 0x04);
  arch_outb(0xA1, 0x02);
  arch_outb(0x21, 0x01);
  arch_outb(0xA1, 0x01);
  arch_outb(0x21, 0x0);
  arch_outb(0xA1, 0x0);

  // Complete!
  irq_install();

  DLOG("PIC Ready!");
  __asm volatile ("sti");
}
