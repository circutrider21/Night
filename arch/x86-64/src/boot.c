#include <arch/bootboot.h>
#define MODULE_NAME "ARCH_INIT"
#include <kernel/qemu.h>
#include <kernel.h>

extern BOOTBOOT bootboot;               
extern unsigned char environment[4096];
extern u8 fb;

handover_t trt;

static void init_handover() {
	trt.arch_name = "x86-64";
	trt.arch_type = 2;
	trt.framebuffer = (void*)0xB8000;
	trt.height = 25;
	trt.width = 80;
	trt.pitch = 0;
}

void _start() {
  DINIT();
  DLOG("Just Booted!");
	init_handover();
  for(;;) {
    __asm volatile ("hlt");
  }
//	kmain(&trt);
}
