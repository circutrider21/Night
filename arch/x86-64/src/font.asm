[BITS 64]
section .data

global font_start
global font_end
global font_sz

font_start:
  incbin "./font.psf"
font_end:

font_sz: equ font_end - font_start