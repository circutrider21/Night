#ifndef NIGHT_LOGGER_H
#define NIGHT_LOGGER_H

#include <libk/types.h>

// This is a serial logger that logs to COM1
// It is used throught the kernel for debug purposes

#define DLOG(k, ...) __log(MODULE_NAME, k, #__VA_ARGS__)

// A Simple Logger function that logs to the serial console
void __log(char* modname, char* fmt, ...);
void init_logger();

#endif // NIGHT_LOGGER_H