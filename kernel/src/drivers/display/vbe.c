#include <drivers/display/vbe.h>
#include "font.h"

#define RED_SHIFT 16
#define GREEN_SHIFT 8
#define BLUE_SHIFT 0

static vbe_color_t fg_color = {255, 255, 255};
static vbe_color_t bg_color = {0, 0, 0};
static size_t cursor_x, cursor_y = 5;
static u32 _width, _height, _pitch = 0;
static u32* fb = NULL;

// Small color-related helper functions
// Make my job easier
static u32 get_color(vbe_color_t *color) {
    return (u32)((color->r << RED_SHIFT) | (color->g << GREEN_SHIFT) | (color->b << BLUE_SHIFT));
}

void vbe_setcolor(vbe_color_t fg, vbe_color_t bg) {
    fg_color = fg;
    bg_color = bg;
}

static void pres_putchar(char character, int position_x, int position_y, vbe_color_t color) {
    u8 iy, ix;
    for (iy = 0; iy < 8; iy++) {
        for (ix = 0; ix < 8; ix++) {
            if ((font[(u8)character][iy] >> ix) & 1) {
                u64 offset = ((iy + position_y) * _pitch) + ((ix + position_x) * 4);
                *(u32 *)((u64)fb + offset) = get_color(&color);
            }
        }
    }
}

void vbe_putc(char c) {
    if (c == '\n') {
        cursor_x = 5;
        cursor_y += 20;
    }
    if (c == '\0') {
        cursor_x -= 1;
        pres_putchar(' ', cursor_x, cursor_y, fg_color);
        cursor_x++;
    } else {
        pres_putchar(c, cursor_x, cursor_y, fg_color);
        cursor_x += 8;

        if (cursor_x >= _width - 5) {
            cursor_x = 5;
            cursor_y += 10;
        }
    }
}

void vbe_pixel(size_t x, size_t y, vbe_color_t clr) {
    size_t index = x + (_pitch / sizeof(u32)) * y;

    fb[index] = get_color(&clr);
}

void vbe_puts(char *string) {
    while (*string) {
        vbe_putc(*string++);
    }
}

void vbe_clear() {
    int i, j;
    for (i = 0; i < _width; i++) {
        for (j = 0; j < _height; j++) {
            vbe_pixel(i, j, bg_color);
        }
    }
}

int vbe_init(handover_t* hd) {
    if(hd->pitch == 0) {
      return 0;
    } else {
        fb = (u32*)hd->framebuffer;
        _width = hd->width;
        _height = hd->height;
        _pitch = hd->pitch;
        vbe_clear();
        return 1;
    }
}

