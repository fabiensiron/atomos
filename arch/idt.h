#ifndef _IDT_H
#define _IDT_H

#include <arch/ioport.h>
#include <arch/exception.h>
#include <include/kernel.h>
#include <include/stdlib.h>
#include <drivers/i8259.h>
#include <drivers/vga_text.h>

#define SIZE_IDT 48

extern void init_interrupts ();
extern void exception_handler ();
extern void interrupt_handler ();

extern void error_isr (u8);

extern void set_idt_handler (u8,u32,u8);

extern void load_idt (void);

void critical_exception (void);
void no_error_wrapper (void);
void error_wrapper (void);

#endif /* _IDT_H */
