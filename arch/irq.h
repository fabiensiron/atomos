#ifndef _IRQ_H_
#define _IRQ_H_

#include <arch/idt.h>
#include <drivers/i8259.h>

#define PIT 0
#define KEYBOARD 1

extern void init_irq (void);


/* assembly */
extern void keyboard_IRQ ();


#endif /* _IRQ_H_ */
