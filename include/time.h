#ifndef _TIME_H_
#define _TIME_H_

#include <include/kernel.h>
#include <drivers/i8253.h>

# define PAUSE_DELAY 5000000

extern void pause (void);
extern void sleep (u16);

#endif /* _TIME_H_ */
