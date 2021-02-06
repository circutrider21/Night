#include <arch/arch.h>


u8 arch_inb(u16 _port) {
	u8 rv;
	__asm volatile ("inb %1, %0" : "=a"(rv) : "dN"(_port));
  return rv;
}

void arch_outb(u16 _port, u8 _data) {
  __asm __volatile__("outb %1, %0" : : "dN"(_port), "a"(_data));
}

void arch_halt() {
	__asm volatile ("cli");
	__asm volatile ("hlt");
	for(;;);
}


