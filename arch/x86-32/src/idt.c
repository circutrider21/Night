#include <arch/idt.h>

idt_entry idt[256]; 
idt_ptr idtp;

extern void _idt_load();

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
                  unsigned char flags) {
  idt[num].base_lo = (base & 0xFFFF);
  idt[num].base_hi = (base >> 16) & 0xFFFF;

  idt[num].sel = sel;
  idt[num].always0 = 0;
  idt[num].flags = flags;
}

void *memset(void *dest, char val, size_t count) {
  char *temp = (char *)dest;
  for (; count != 0; count--) *temp++ = val;
  return dest;
}

/* Installs the IDT */
void init_idt() {
  idtp.limit = (sizeof(idt_entry) * 256) - 1;
  idtp.base = &idt;

  memset(&idt, 0, sizeof(idt_entry) * 256);

  _idt_load();
}
