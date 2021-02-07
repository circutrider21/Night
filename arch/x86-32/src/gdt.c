#include <arch/gdt.h>

gdt_entry entries[5];
gdt_table gdt;

extern flush_gdt(u32 gdt_ptr);

static void set_gate(int num, u32 base, u32 limit, u8 access, u8 gran) {
  entries[num].base_low    = (base & 0xFFFF);
  entries[num].base_middle = (base >> 16) & 0xFF;
  entries[num].base_high   = (base >> 24) & 0xFF;

  entries[num].limit_low   = (limit & 0xFFFF);
  entries[num].granularity = (limit >> 16) & 0x0F;

  entries[num].granularity |= gran & 0xF0;
  entries[num].access      = access;
}

void init_gdt() {
  gdt.limit = (sizeof(gdt_entry) * 5) - 1;
  gdt.base  = (u32)&entries;

  set_gate(0, 0, 0, 0, 0);                // Null segment
  set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
  set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
  set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
  set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

  flush_gdt((u32)&gdt);
}