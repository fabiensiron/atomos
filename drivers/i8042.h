/*
 *  Set-up the 8042 chip which deal with PS/2 and other stuffs
 *  Also, it refreshes the last keyboard key press.
 */

#ifndef _i8042_H
#define _i8042_h

#include <include/kernel.h>
#include <drivers/vga_text.h>
#include <arch/ioport.h>
#include <include/stdio.h>
#include <include/stdlib.h>

#define I8042_DATA 0x60
#define I8042_COMMAND 0x64

#define KEYPRESSED  0
#define KEYRELEASED 1

#define SC_NULL 0xff
#define SC_ENTER 0xfe 

bool_t keyboard_new_event;
u8 keyboard_lastkeypressed;
u8 input_buffer[80];
u8 input_buffer_cursor;

extern void refresh_ps2_controller ();
extern void wait_input (char* buffer);


#endif /* _i8042_H */
