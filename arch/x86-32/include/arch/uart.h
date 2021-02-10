#ifndef NIGHT_UART_H
#define NIGHT_UART_H

#include <libk/types.h>

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

void arch_init_uart(u16 port);

void arch_uart_putc(u16 port, char c);
char arch_uart_getc(u16 port);


#endif // NIGHT_UART_H