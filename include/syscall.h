#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <include/kernel.h>
#include <include/mem.h>
#include <drivers/i8042.h>
#include <drivers/vga_text.h>
#include <arch/pm.h>

#define SYS_WRITE 1
#define SYS_READ 2
#define SYS_SBRK 3

extern void syscall (u32 num, u32 arg);


#endif /* _SYSCALL_H */
