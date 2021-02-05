#ifndef ARCH_HANDOVER_H
#define ARCH_HANDOVER_H

#include <libk/types.h>

typedef struct {
	char* arch_name;
	int arch_type; // 1 for 32 | 2 for 64

	void* framebuffer;
	size_t height;
	size_t width;
	int pitch; // 0 means CGA Textmode

	void* ramdisk;
	size_t len;
} handover_t;

#endif // ARCH_HANDOVER_H