#ifndef _I8253_H_
#define _I8253_H_

#include <include/kernel.h>
#include <include/stdio.h>
#include <arch/ioport.h>

# define PIT_CH0 0x40
# define PIT_CH1 0x41
# define PIT_CH3 0x42
# define PIT_CMD 0x43

/* frequency in hertz */
# define PIT_ORIG_FREQ 1193182
# define PIT_FREQ 1000

static u32 count;

extern void pit_init ();
extern void pit_handler ();
extern void pit_reset_count ();
extern u32 pit_get_count ();

#endif /* _I8253_H_ */
