#include <arch/arch.h>
#include <arch/uart.h>

void arch_init_uart(u16 port) {
  arch_outb(port + 1, 0x00);    // Disable all interrupts
  arch_outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
  arch_outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
  arch_outb(port + 1, 0x00);    //                  (hi byte)
  arch_outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
  arch_outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
  arch_outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
  arch_outb(port + 4, 0x1E);    // Set in loopback mode, test the serial chip
  arch_outb(port + 4, 0x0F);
}

int is_transmit_empty(u16 p) {
  return arch_inb(p + 5) & 0x20;
}
 
void arch_uart_putc(u16 port, char c) {
  while (is_transmit_empty(port) == 0);
 
  arch_outb(port, c);
}

int serial_received(u16 p) {
  return arch_inb(p + 5) & 1;
}
 
char arch_uart_getc(u16 port) {
  while (serial_received(port) == 0);
 
  return arch_inb(port);
}
