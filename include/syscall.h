#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <include/kernel.h>
#include <include/stdio.h>
#include <drivers/i8042.h>

#define SYS_WRITE 1
#define SYS_READ 2
#define SYS_SBRK 3

extern u32 sys_sbrk(u32 offset);
extern void syscall (u32 num, u32 arg);


#endif /* _SYSCALL_H */