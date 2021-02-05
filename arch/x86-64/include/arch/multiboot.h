#pragma once

#include <libk/types.h>

#define MULTIBOOT_MAGIC 0x1BADB002
#define MULTIBOOT_EAX_MAGIC 0x2BADB002
#define MULTIBOOT_FLAG_MEM (1 << 0)
#define MULTIBOOT_FLAG_DEVICE (1 << 1)
#define MULTIBOOT_FLAG_CMDLINE (1 << 2)
#define MULTIBOOT_FLAG_MODS (1 << 3)
#define MULTIBOOT_FLAG_AOUT (1 << 4)
#define MULTIBOOT_FLAG_ELF (1 << 5)
#define MULTIBOOT_FLAG_MMAP (1 << 6)
#define MULTIBOOT_FLAG_DRIVES (1 << 7)
#define MULTIBOOT_FLAG_CONFIG (1 << 8)
#define MULTIBOOT_FLAG_LOADER (1 << 9)
#define MULTIBOOT_FLAG_APM (1 << 10)
#define MULTIBOOT_FLAG_VBE (1 << 11)
#define MULTIBOOT_FRAMEBUFFER (1 << 12)

typedef struct {
  void* mod_start;
  void* mod_end;
  char* string;
  u32 reserved;
} mod_t;

typedef struct {
  u32 size;
  u32 addr;
  u32 length;
  u32 type;
} __attribute__((packed)) mmap_t;

typedef struct {
  u32 address;
  u32 pitch;
  u32 width;
  u32 height;
  u8 bpp;
  u8 type;
  u8 red_position;
  u8 red_mask_size;
  u8 green_position;
  u8 green_mask_size;
  u8 blue_position;
  u8 blue_mask_size;
} __attribute__((packed)) fb_info_t;

typedef struct {
  u32* flags;
  u32* mem_lower;
  u32* mem_upper;
  u32* boot_device;
  u32* cmdline;
  u32* mods_count;
  u32* mods_addr;
  u32* num;
  u32* size;
  u32* addr;
  u32* shndx;
  u32* mmap_length;
  u32* mmap_addr;
  u32* drives_length;
  u32* drives_addr;
  u32* config_table;
  u32* boot_loader_name;
  u32* apm_table;
  /* VBE */
  u32* vbe_control_info;
  u32* vbe_mode_info;
  u16 vbe_mode;
  u16 vbe_interface_seg;
  u16 vbe_interface_off;
  u16 vbe_interface_len;
  /* framebuffer */
  fb_info_t framebuffer;
} __attribute__((packed)) multiboot;
