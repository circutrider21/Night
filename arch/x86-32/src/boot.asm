; Copyright (c) 2021 Peeled Fruit Studios

[BITS 32]
global _start
_start:
    mov esp, __stack  
    push ebx   
    jmp stublet

[section .multiboot]
  ; Multiboot macros to make a few lines later more readable
  MULTIBOOT_PAGE_ALIGN	equ 1<<0
  MULTIBOOT_MEMORY_INFO	equ 1<<1
  MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
  MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
  MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

  ; This is the GRUB Multiboot header. A boot signature
  dd MULTIBOOT_HEADER_MAGIC
  dd MULTIBOOT_HEADER_FLAGS
  dd MULTIBOOT_CHECKSUM


stublet:
    extern arch_main
    call arch_main
    jmp $

section .text

global flush_gdt

flush_gdt:
  mov eax, [esp+4]
  lgdt [eax]        ; Load the new GDT pointer
  mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
  mov ds, ax        ; Load all data segment selectors
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x08:.flush
.flush:
  ret

global _idt_load
extern idtp
_idt_load:
    lidt [idtp]
    ret

[section .bss]
	resb 8192
__stack: