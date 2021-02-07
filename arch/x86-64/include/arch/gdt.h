#ifndef ARCH_X64_GDT_H
#define ARCH_X64_GDT_H

#include <libk/types.h>

typedef struct {
  u16 limit;
  u16 base_low16;
  u8  base_mid8;
  u8  access;
  u8  granularity;
  u8  base_high8;
} __attribute__((packed)) gdt_entry;

typedef struct {
  u16 size;
  u64 address;
} __attribute__((packed)) gdt_table;

void init_gdt();

#endif // ARCH_X64_GDT_H