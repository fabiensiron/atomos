/*
 *  Set-up the 8042 chip which deal with PS/2 and other stuffs
 *  Also, it refreshes the last keyboard key press.
 */

#ifndef _i8042_H
#define _i8042_h

#include <include/kernel.h>
#include <arch/ioport.h>

#define I8042_DATA 0x60
#define I8042_COMMAND 0x64

#define KEYPRESSED 1
#define KEYRELEASED 0

bool_t keyboard_new_event;
u8 keyboard_lastkeypressed;

extern void refresh_ps2_controller ();


#endif /* _i8042_H */
