#include "i8042.h"

#define SC_NULL 0xff

static char sc_table[] = 
  {
    SC_NULL, SC_NULL,  // 0x0
    '1','2','3','4','5','6','7','8','9','0', // 0x1
    '-','=',SC_NULL,SC_NULL,  // 0x0c
    'q','w','e','r','t','y','u','i','o','p', // 0x10
    '[',']',SC_NULL,SC_NULL, // 0x1A
    'a','s','d','f','g','h','j','k','l', // 0x1e
    ';','\'','`',SC_NULL,'\\', //0x27
    'z','x','c','v','b','n','m', // 0x2c
    ',','.','/',SC_NULL,'*',SC_NULL,' ',SC_NULL, //0x33
    SC_NULL,SC_NULL,SC_NULL,SC_NULL,SC_NULL,SC_NULL,SC_NULL,SC_NULL, // 0x3B
    SC_NULL,SC_NULL, // 0x43
    SC_NULL,SC_NULL, // 0x45
    '7','8','9','-','4','5','6','+', // 0x47
    '1','2','3','0','.', // 0x4f
    SC_NULL,SC_NULL,SC_NULL, // 0x54
    SC_NULL,SC_NULL // 0x57
  };


static u8 get_type (u8 c_) {
  return (c_ & 0x80)?KEYPRESSED:KEYRELEASED;
}

static u8 get_scan_code (u8 c_) {
  return c_ & 0x7f; 
}

static char scan_to_ascii (u8 sc_) {
  char str[] = {sc_table[sc_], '\0'};
  write_text_vga (str); 
}

/* just for test */

extern void refresh_ps2_controller () {

  while (((INB(I8042_COMMAND)) & 1) == 0)
      ;

  u8 c = INB (0x60);

  if (get_type(c) != KEYRELEASED)
    return;
  u8 sc = get_scan_code (c);
  scan_to_ascii (sc);
}


