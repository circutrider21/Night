extern arch_main
global _start

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

section .text
bits 32
_start:
  mov eax, p3_table
  or eax, 0b11 ; 
  mov dword [p4_table + 0], eax

  mov eax, p2_table
  or eax, 0b11
  mov dword [p3_table + 0], eax

  mov ecx, 0
.map_p2_table:
  mov eax, 0x200000  ; 2MiB
  mul ecx
  or eax, 0b10000011
  mov [p2_table + ecx * 8], eax

  inc ecx
  cmp ecx, 512
  jne .map_p2_table

  ; move page table address to cr3
  mov eax, p4_table
  mov cr3, eax

  ; enable PAE
  mov eax, cr4
  or eax, 1 << 5
  mov cr4, eax

  ; set the long mode bit
  mov ecx, 0xC0000080
  rdmsr
  or eax, 1 << 8
  wrmsr

  ; enable paging
  mov eax, cr0
  or eax, (1 << 31 | 1 << 16)
  mov cr0, eax

  lgdt [gdt64.pointer]

  ; update selectors
  mov ax, gdt64.data
  mov ss, ax
  mov ds, ax
  mov es, ax

  jmp gdt64.code:arch_main

  hlt

section .bss
align 4096
p4_table:
  resb 4096
p3_table:
  resb 4096
p2_table:
  resb 4096

section .rodata
gdt64:
  dq 0
.code: equ $ - gdt64
  dq (1<<44) | (1<<47) | (1<<41) | (1<<43) | (1<<53)
.data: equ $ - gdt64
  dq (1<<44) | (1<<47) | (1<<41)
.pointer:
  dw $ - gdt64 - 1
  dq gdt64