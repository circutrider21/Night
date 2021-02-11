#ifndef ARCH_X64_IDT_H
#define ARCH_X64_IDT_H

#include <libk/types.h>

typedef struct {
  u16 offset_low;
  u16 selector;
  u8 ist;
  u8 types_attr;
  u16 offset_mid;
  u32 offset_high;
  u32 zero;
} __attribute__((packed)) idt_entry;

typedef struct {
  u16 segment;
  u64 offset;
} __attribute__((packed)) idt_table;

__attribute__((packed)) struct cpu_state {
  u64 r15;
  u64 r14;
  u64 r13;
  u64 r12;
  u64 r11;
  u64 r10;
  u64 r9;
  u64 r8;
  u64 rbp;
  u64 rdi;
  u64 rsi;
  u64 rdx;
  u64 rcx;
  u64 rbx;
  u64 rax;

  u64 intno;
  u64 err;

  // the interrupt stackframe
  u64 rip;
  u64 cs;
  u64 rflags;
  u64 rsp;
  u64 ss;
};

void add_handler(int pos, u64 addr, u8 flags);

void init_idt();

#endif // ARCH_X64_IDT_H