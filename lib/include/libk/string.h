#ifndef LIBK_PRINT_H
#define LIBK_PRINT_H

#include "stdarg.h"
#include "types.h"

void sprintf(char* buf, char* fmt, ...);
size_t strlen(const char* s);
char* ssplit(char to_split, char* src, char* rem);
char *strtok(char *s, const char* delim);
char *strdup(char *str);

#endif