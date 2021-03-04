libarch_src = files(
  'src/arch.c',
  'src/boot.c',
  'src/gdt.c',
  'src/idt.c',
  '../x86-32/src/uart.c'
)

libarch_inc = include_directories('../../kernel/include', '../../lib/include', './include')

nasm_sources = files(
  'src/isrs.asm',
  'src/early.asm'
)

nasm = find_program('nasm')
nasm_gen = generator(nasm, output: '@BASENAME@.o', arguments: ['-f', 'elf64', '@INPUT@', '-o', '@OUTPUT@'])
nasm_obj = nasm_gen.process(nasm_sources)

libarch = static_library('libarch', nasm_obj, libarch_src, include_directories: libarch_inc, c_args: cflags)

