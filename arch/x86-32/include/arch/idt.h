#ifndef ARCH_X32_IDT_H
#define ARCH_X32_IDT_H

#include <libk/types.h>

// IDT Stuff --------------------------------------------

typedef struct {
  u16 base_lo;
  u16 sel;
  u8 always0;
  u8 flags;
  u16 base_hi;
} __attribute__((packed)) idt_entry;

typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) idt_ptr;

void init_idt();

// ISR Stuff --------------------------------------------

struct regs {
  unsigned int gs, fs, es, ds;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned int int_no, err_code;
  unsigned int eip, cs, eflags, useresp, ss;
};

typedef struct regs regs;

extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

void install_isr();

// IRQ Stuff

void add_irq_handler(u8 slot, void* handler);

#endif // ARCH_X32_IDT_H