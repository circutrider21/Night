#include <arch/idt.h>
#include <drivers/display/vbe.h>
#define MODULE_NAME "IDT"
#include <kernel/logger.h>

#define INTGATE 0x8e

idt_entry _idt[256] = {};
extern u64 __interrupt_vector[];
idt_table _idt_descriptor = {
  .segment = sizeof(idt_entry) * 256,
  .offset = (u64)&_idt,
};

extern void load_idt(u64 descriptor);

void add_handler(int pos, u64 addr, u8 flags) {
  _idt[pos] = (idt_entry){
    .ist = 0,
    .types_attr = flags,
    .selector = 0x08,
    .offset_low = addr & 0xffff,
    .offset_mid = (addr >> 16) & 0xffff,
    .offset_high = (addr >> 32) & 0xffffffff,
    .zero = 0,
  };
}

void init_idt() {
  for(int g = 0; g < 48; g++) {
    add_handler(g, __interrupt_vector[g], INTGATE);
  }
  load_idt((u64)&_idt_descriptor);
  DLOG("Interrupts Initialized!\n");
}
// ISR Stuff --------------------------------------

static const char *_exception_messages[32] = {
  "Division by zero",
  "Debug",
  "Non-maskable interrupt",
  "Breakpoint",
  "Detected overflow",
  "Out-of-bounds",
  "Invalid opcode",
  "No coprocessor",
  "Double fault",
  "Coprocessor segment overrun",
  "Bad TSS",
  "Segment not present",
  "Stack fault",
  "General protection fault",
  "Page fault",
  "Unknown interrupt",
  "Coprocessor fault",
  "Alignment check",
  "Machine check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
};

void handle_interrupt(struct cpu_state* ctx) {
  DLOG("Interrupt Called\n");
  if(ctx->intno < 32) {
    DLOG("int_no = %d\n", ctx->intno);
    vbe_putc('\n');
    vbe_puts(_exception_messages[ctx->intno]);
    vbe_puts(" Exception. System Halted!");
  }
}