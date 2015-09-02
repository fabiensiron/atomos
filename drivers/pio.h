#ifndef _PIO_H
#define _PIO_H

#include <include/kernel.h>
#include <include/log.h>
#include <include/time.h>
#include <arch/ioport.h>

extern int pio_read (int drive_, u32 lba_, int count_,
    u8* buf_);

extern int pio_write (int drive_, int numblock_, int count_,
    u8* buf_);

#endif /* _PIO_H */
