#ifndef ARCH_X32_GDT_H
#define ARCH_X32_GDT_H

#include <libk/types.h>

// A 32-bit GDT (And later TSS)

typedef struct {
  u16 limit_low;
  u16 base_low;
  u8  base_middle;
  u8  access; 
  u8  granularity;
  u8  base_high;
} __attribute__((packed)) gdt_entry;

typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) gdt_table;

// Installs GDT onto the system
void init_gdt();

#endif // ARCH_X32_GDT_H