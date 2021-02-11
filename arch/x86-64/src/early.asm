[BITS 64]

section .text

global reload_gdt
extern gdt
reload_gdt:
  lgdt [gdt]
  push rbp
  mov rbp, rsp

  push qword 0x10
  push rbp
  pushf
  push qword 0x8
  push .trampoline
  iretq

.trampoline:
  pop rbp

  mov ax, 0x10

  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  ret

global load_idt
load_idt:
  lidt [rdi]
  ret

section .bss
	resb 8192
__stack: