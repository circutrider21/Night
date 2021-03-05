#ifndef NIGHT_PIC_8259_H
#define NIGHT_PIC_8259_H

#include <libk/types.h>
#include <arch/arch.h>

// Since there is no timer yet...
// You can wait by writing garbage to port 0x80
// Earlier versions of linux and windows handeled it like this

#define IO_WAIT() (arch_outb(0x80, 0))

// Command for readying PIC
#define INIT_CMD 0x11

// Data and Command ports
#define PIC0_CMD 0x20
#define PIC0_DATA 0x21

#define PIC1_CMD 0xA0
#define PIC1_DATA 0xA1

void init_pic();

#endif // NIGHT_PIC_8259_H