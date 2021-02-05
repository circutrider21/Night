#include <libk/memory.h>


void* memcpy(void *dest, const void *src, size_t count) {
  const char *sp = (const char *)src;
  char *dp = (char *)dest;
  for (; count != 0; count--) *dp++ = *sp++;
  return dest;
}

int memcmp(u8* uno, u8* dos, int num) {
  for(int k = 0; k < num; k++) {
    if(uno[k] != dos[k]) {
      return 1;
    }
  }

  return 0;
}

void *memset(void *dest, char val, size_t count) {
  char *temp = (char *)dest;
  for (; count != 0; count--) *temp++ = val;
  return dest;
}

u16 *memsetw(u16 *dest, u16 val, size_t count) {
  u16 *temp = (u16 *)dest;
  for (; count != 0; count--) *temp++ = val;
  return dest;
}
