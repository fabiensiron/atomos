#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <include/kernel.h>
#include <include/stdio.h>

#define SYS_WRITE 1

extern void syscall (u32 num, u32 arg);


#endif /* _SYSCALL_H */
