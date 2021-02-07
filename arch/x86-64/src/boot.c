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
	trt.framebuffer = (void*)fb;
	trt.height = bootboot.fb_height;
	trt.width = bootboot.fb_width;
	trt.pitch = 32;
}

void _start() {
  DLOG("Just Booted!");
	init_handover();
  init_gdt();
  kmain(&trt);
}
