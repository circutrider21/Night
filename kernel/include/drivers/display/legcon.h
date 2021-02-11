#ifndef NIGHT_LEGACY_CONSOLE_H
#define NIGHT_LEGACY_CONSOLE_H

#include <libk/types.h>
#include <arch/handover.h>

/* The legacy console is a text-based vga framebuffer                                                    *
*  It is almost always located at 0xB8000 and is always 80 x 25.                                         *
*  Finally, the legacy console is not supported on x86-64 EFI afaik, so it is not used on that platform  */

typedef enum {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
} colors;

void lcon_putc(char c);
void lcon_setcolor(u8 fg, u8 bg);
void lcon_puts(char* s);
void lcon_clear();
int lcon_init(handover_t* h); // Returns 1 if legacy console is supported, otherwise returns 0

#endif // NIGHT_LEGACY_CONSOLE_H