#ifndef __STIVALE__STIVALE_H__
#define __STIVALE__STIVALE_H__

#include <libk/types.h>

/* --- Header --------------------------------------------------------------- */
/*  Information passed from the kernel to the bootloader                      */

struct stivale_header {
    u64 stack;
    u16 flags;
    u16 framebuffer_width;
    u16 framebuffer_height;
    u16 framebuffer_bpp;
    u64 entry_point;
} __attribute__((packed));

/* --- Struct --------------------------------------------------------------- */
/*  Information passed from the bootloader to the kernel                      */

struct stivale_module {
    u64 begin;
    u64 end;
    char string[128];
    u64 next;
} __attribute__((packed));

enum {
    STIVALE_MMAP_USABLE = 1,
    STIVALE_MMAP_RESERVED = 2,
    STIVALE_MMAP_ACPI_RECLAIMABLE = 3,
    STIVALE_MMAP_ACPI_NVS = 4,
    STIVALE_MMAP_BAD_MEMORY = 5,
    STIVALE_MMAP_KERNEL_AND_MODULES = 10,
    STIVALE_MMAP_BOOTLOADER_RECLAIMABLE = 0x1000
};

struct stivale_mmap_entry {
    u64 base;
    u64 length;
    u32 type;
    u32 unused;
} __attribute__((packed));

enum {
    STIVALE_FBUF_MMODEL_RGB = 1
};

struct stivale_struct {
    u64 cmdline;
    u64 memory_map_addr;
    u64 memory_map_entries;
    u64 framebuffer_addr;
    u16 framebuffer_pitch;
    u16 framebuffer_width;
    u16 framebuffer_height;
    u16 framebuffer_bpp;
    u64 rsdp;
    u64 module_count;
    u64 modules;
    u64 epoch;
    u64 flags; // bit 0: 1 if booted with BIOS, 0 if booted with UEFI
                    // bit 1: 1 if extended colour information passed, 0 if not
    u8  fb_memory_model;
    u8  fb_red_mask_size;
    u8  fb_red_mask_shift;
    u8  fb_green_mask_size;
    u8  fb_green_mask_shift;
    u8  fb_blue_mask_size;
    u8  fb_blue_mask_shift;
} __attribute__((packed));

#endif