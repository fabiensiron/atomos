#ifndef _SYSCALL_H
#define _SYSCALL_H_

#include <stdio.h>

#define SYSCALL_INT_NUM 0x80
#define SYSCALL_INT "int $0x80\n"

#define SYSCALL(i,arg) ({ \
  unsigned int _v;    \
    __asm__ volatile( \
      "mov %1, %%ebx \n"  \
      "mov %2, %%eax \n" \
      SYSCALL_INT \
      "mov %%eax, %0 \n" \
      : "=a"(_v)\
      : "b"(arg), "i"(i) \
        : \
      ); \
    _v; \
  }) \

#define SYS_WRITE 1
#define SYS_READ  2
#define SYS_SBRK  3
#define SYS_SLEEP 4

extern void write (char* str);
extern unsigned int read (char* buffer);
extern void* sbrk (unsigned int offset);
extern void _sleep (unsigned long t);

#endif /* _SYSCALL_H */
