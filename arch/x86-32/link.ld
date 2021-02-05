ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
  . = 0x0100000;

  .text :
  {
    *(.multiboot)
    *(.text*)
    *(.rodata)
  }

  .data  :
  {

    *(.data)
  }

  .bss  :
  {
    *(.bss)
  }
  end = .; _end = .; __end = .;
  /DISCARD/ : { *(.fini_array*) *(.comment) }
}