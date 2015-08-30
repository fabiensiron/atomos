#ifndef _STDIO_H
#define _STDIO_H

#include <drivers/vga_text.h>
#include <drivers/serial.h>
#include <include/stdarg.h>
#include <include/config.h>

//extern void(*putc)(char c);
//putc = &putc_text_vga;

int vprintf(char* fmt, va_list args);
int kprintf(char* fmt, ...);

void kout_init ();


#endif /* _STDIO_H */
