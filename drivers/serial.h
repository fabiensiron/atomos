#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <include/kernel.h>
#include <arch/ioport.h>

# define COM1 0x3f8
# define COM2 0x2f8
# define COM3 0x3e8
# define COM4 0x2e8

# define BAUDRATE 38400
# define SERIAL_CLK_FREQ 115200

extern void serial_init ();
extern void serial_putc (char c_);

# endif /* _SERIAL_H_ */
