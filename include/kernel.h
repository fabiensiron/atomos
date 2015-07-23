#ifndef _KERNEL_H
#define _KERNEL_H

#include <include/errno.h>
#include <include/stdarg.h>
#include <include/stddef.h>
#include <include/stdlib.h>
#include <include/string.h>

typedef unsigned char      u8;
typedef unsigned short int u16;
typedef unsigned long int  u32;
typedef unsigned long long u64;
typedef char               s8;
typedef short              s16;
typedef int                s32;
typedef long long          s64;

typedef unsigned char bool_t;
#define TRUE 1
#define FALSE 0

void panic (const char* msg);

void* brk;
void* entry;

#endif /* _KERNEL_H */
