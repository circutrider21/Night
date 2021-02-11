#ifndef NIGHT_VBE_H
#define NIGHT_VBE_H

#include <libk/types.h>
#include <arch/handover.h>

/* This is a Generic framebuffer driver that writes to a framebuffer directly *
*  The framebuffer that this driver uses is from the handover protocol        */

// A type that repersents a color

typedef struct {
    u8 r, g, b;
} vbe_color_t;

int vbe_init(handover_t* hd); // Returns 1 if VBE is supported on this platform, else returns 0
void vbe_setcolor(vbe_color_t fg, vbe_color_t bg);

void vbe_putc(char c);
void vbe_puts(char* s);

void vbe_clear();
void vbe_pixel(size_t x, size_t y, vbe_color_t clr);

#endif // NIGHT_VBE_H