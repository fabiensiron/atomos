#ifndef _STDIO_H
#define _STDIO_H

//#include <drivers/vga_text.h>
#include <stdarg.h>
#include <syscall.h>

//extern void(*putc)(char c);
//putc = &putc_text_vga;

int vprintf(char* fmt, va_list args);
extern int printf(char* fmt, ...);



#endif /* _STDIO_H */
