#include <arch/bootboot.h>
#include <arch/uart.h>
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

void arch_main() {
    arch_init_uart(COM1);
    arch_uart_putc(COM1, '!');
    init_handover();
    init_gdt();
    kmain(&trt);
}
