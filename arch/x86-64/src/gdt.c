#include <arch/gdt.h>

gdt_entry entries[5];
gdt_table gdt;

static void reload_gdt(void) {
  __asm volatile (
    "lgdt %0\n\t"
    "push %1\n\t"
    "push OFFSET\n\t"
    "lretq\n\t"
    "1:\n\t"
    "mov ds, %2\n\t"
    "mov es, %2\n\t"
    "mov fs, %2\n\t"
    "mov gs, %2\n\t"
    "mov ss, %2\n\t"
    :
    : "m"(gdt), "rmi"((u64)0x08), "rm"((u64)0x10)
    : "memory"
    );
}

void init_gdt() {

  // Null Segment
  entries[0].limit       = 0;
  entries[0].base_low16  = 0;
  entries[0].base_mid8   = 0;
  entries[0].access      = 0;
  entries[0].granularity = 0;
  entries[0].base_high8  = 0;

  // Kernel code 64.
  entries[1].limit       = 0;
  entries[1].base_low16  = 0;
  entries[1].base_mid8   = 0;
  entries[1].access      = 0b10011010;
  entries[1].granularity = 0b00100000;
  entries[1].base_high8  = 0;

   // Kernel data 64.
  entries[2].limit       = 0;
  entries[2].base_low16  = 0;
  entries[2].base_mid8   = 0;
  entries[2].access      = 0b10010010;
  entries[2].granularity = 0;
  entries[2].base_high8  = 0;

   // User data 64.
  entries[3].limit       = 0;
  entries[3].base_low16  = 0;
  entries[3].base_mid8   = 0;
  entries[3].access      = 0b11110010;
  entries[3].granularity = 0;
  entries[3].base_high8  = 0;

   // User code 64.
  entries[4].limit       = 0;
  entries[4].base_low16  = 0;
  entries[4].base_mid8   = 0;
  entries[4].access      = 0b11111010;
  entries[4].granularity = 0b00100000;
  entries[4].base_high8  = 0;

  // Set the pointer.
  gdt.size = (sizeof(gdt_entry) * 5) - 1;
  gdt.address  = (u64)&entries;

  reload_gdt();
}