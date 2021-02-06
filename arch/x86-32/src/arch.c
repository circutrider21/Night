#include <arch/arch.h>
#include <arch/multiboot.h>
#include <arch/handover.h>
#define MODULE_NAME "ARCH_INIT"
#include <kernel/qemu.h>
#include <kernel.h>

handover_t trt;

static void init_handover() {
	trt.arch_name = "x86-32";
	trt.arch_type = 1;
	trt.framebuffer = (void*)0xB8000;
	trt.height = 25;
	trt.width = 80;
	trt.pitch = 0;
}

void arch_main(multiboot* mb) {
  DINIT();
  DLOG("Just Booted!");
	init_handover();
	kmain(&trt);	
}

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