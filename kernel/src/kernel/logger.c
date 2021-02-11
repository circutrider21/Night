#include <kernel/logger.h>
#include <arch/uart.h>
#include <libk/string.h>

static u16 PORT = COM1;

static void logger_puts(char* str) {
  for(int k = 0; k < strlen(str); k++) {
    arch_uart_putc(PORT, str[k]);
  }
}

void __log(char* modname, char* fmt, ...) {
  char bufe[200];
  char buf[300];
  va_list vt;
  va_start(vt, fmt);
  vsprintf(bufe, fmt, vt);
  sprintf(buf, "[%s] - %s\n", modname, bufe);
  logger_puts(buf);
  va_end(vt);
}

void init_logger() {
  arch_init_uart(PORT);
  logger_puts("Kernel Logger Initialized\n");
}