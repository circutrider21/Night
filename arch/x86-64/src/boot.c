#include <arch/stivale.h>
#include <arch/uart.h>
#include <kernel.h>
#define MODULE_NAME "BOOT"
#include <kernel/logger.h>

static u8 stack[4096];
handover_t trt;

static void init_handover(struct stivale_struct* sl) {
	trt.arch_name = "x86-64";
	trt.arch_type = 2;
	trt.framebuffer = (void*)sl->framebuffer_addr;
	trt.height = sl->framebuffer_height;
	trt.width = sl->framebuffer_width;
	trt.pitch = sl->framebuffer_pitch;
	trt.raw_ptr = (void*)sl;
}

void arch_main(struct stivale_struct* sl) {
  init_logger();
  DLOG("Booting...");
  init_handover(sl);
  DLOG("Resolution %d x %d x %d", trt.height, trt.width, sl->framebuffer_bpp);
  init_gdt();
  init_idt();
  kmain(&trt);
}

__attribute__((section(".stivalehdr"), used))
struct stivale_header stivale_hdr = {
  .stack = (u64)stack + sizeof(stack),
  .flags = (1 << 0),

  .framebuffer_width  = 0,
  .framebuffer_height = 0,
  .framebuffer_bpp    = 0,

  .entry_point = &arch_main
};