#ifndef _IDT_H
#define _IDT_H

#include <include/kernel.h>
#include <include/stdlib.h>
#include <drivers/vga_text.h>

extern void init_interrupts ();
extern void exception_handler ();
extern void interrupt_handler ();

#endif /* _IDT_H */
