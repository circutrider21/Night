[BITS 64]

section .text
global _start
extern bootboot
extern arch_main
_start:
  ; Bootstrap a stack
  mov esp, __stack
  mov ebp, esp

  ; Check for (And Stop) AP Processors
  mov eax, 1
  cpuid
  shr ebx, 24
  cmp [bootboot + 0xC], bx
  jne .ap

  ; We are the BSP, proceed to arch_main
  call arch_main
  jmp .ap ; Never reached

.ap:
  ; APs can just halt forever
  cli
  hlt
  jmp .ap


section .bss
	resb 8192
__stack: