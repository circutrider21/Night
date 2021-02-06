#ifndef _BOOTBOOT_H_
#define _BOOTBOOT_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <libk/types.h>

#define BOOTBOOT_MAGIC "BOOT"

// minimum protocol level:
//  hardcoded kernel name, static kernel memory addresses
#define PROTOCOL_MINIMAL 0
// static protocol level:
//  kernel name parsed from environment, static kernel memory addresses
#define PROTOCOL_STATIC  1
// dynamic protocol level:
//  kernel name parsed, kernel memory addresses from ELF or PE symbols
#define PROTOCOL_DYNAMIC 2
// big-endian flag
#define PROTOCOL_BIGENDIAN 0x80

// loader types, just informational
#define LOADER_BIOS 0
#define LOADER_UEFI 1
#define LOADER_RPI  2

// framebuffer pixel format, only 32 bits supported
#define FB_ARGB   0
#define FB_RGBA   1
#define FB_ABGR   2
#define FB_BGRA   3

// mmap entry, type is stored in least significant tetrad (half byte) of size
// this means size described in 16 byte units (not a problem, most modern
// firmware report memory in pages, 4096 byte units anyway).
typedef struct {
  u64   ptr;
  u64   size;
} __attribute__((packed)) MMapEnt;
#define MMapEnt_Ptr(a)  (a->ptr)
#define MMapEnt_Size(a) (a->size & 0xFFFFFFFFFFFFFFF0)
#define MMapEnt_Type(a) (a->size & 0xF)
#define MMapEnt_IsFree(a) ((a->size&0xF)==1||(a->size&0xF)==2)

#define MMAP_USED     0   // don't use. Reserved or unknown regions
#define MMAP_FREE     1   // usable memory
#define MMAP_ACPIFREE 2   // free to use after acpi tables are parsed
#define MMAP_ACPINVS  3   // don't use. Acpi non-volatile
#define MMAP_MMIO     4   // memory mapped IO region

#define INITRD_MAXSIZE 16 //Mb

typedef struct {
  u8    magic[4];    // 'BOOT', first 64 bytes are platform independent
  u32   size;        // length of bootboot structure, minimum 128

  u8    protocol;    // 1, static addresses, see PROTOCOL_* above
  u8    loader_type; // see LOADER_* above
  u8    pagesize;    // in power of two, 12 = 4096
  u8    fb_type;     // framebuffer type, see FB_* above

  unsigned short    timezone;    // in minutes -1440..1440
  u16   bspid;       // Bootsrap processor ID (Local APIC Id on x86_64)

  u8    datetime[8]; // in BCD yyyymmddhhiiss UTC (independent to timezone)

  u64   initrd_ptr;  // ramdisk image position and size
  u64   initrd_size;

  u8    *fb_ptr;     // framebuffer pointer and dimensions
  u32   fb_size;
  u32   fb_width;
  u32   fb_height;
  u32   fb_scanline;

  // the rest (64 bytes) is platform specific
  union {
    struct {
      u64 acpi_ptr;
      u64 smbi_ptr;
      u64 efi_ptr;
      u64 mp_ptr;
      u64 unused0;
      u64 unused1;
      u64 unused2;
      u64 unused3;
    } x86_64;
    struct {
      u64 acpi_ptr;
      u64 mmio_ptr;
      u64 unused0;
      u64 unused1;
      u64 unused2;
      u64 unused3;
      u64 unused4;
      u64 unused5;
    } aarch64;
  };

  /* from 128th byte, MMapEnt[], more records may follow */
  MMapEnt    mmap;
  /* use like this: 
   * MMapEnt *mmap_ent = &bootboot.mmap; mmap_ent++; 
   * until you reach bootboot->size */
} __attribute__((packed)) BOOTBOOT;


#ifdef  __cplusplus
}
#endif

#endif