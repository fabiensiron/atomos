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

typedef enum {FALSE = 0, TRUE} atomos_bool_t;

void panic (const char* msg);

#endif /* _KERNEL_H */
