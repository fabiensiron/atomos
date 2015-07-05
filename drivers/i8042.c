#include "i8042.h"

static u8 get_type (u8 c_) {
  return (c_ & 0x80)?KEYPRESSED:KEYRELEASED;
}

static u8 get_scan_code (u8 c_) {
  return c_ & 0x7f; 
}

/* just for test */

extern void refresh_ps2_controller () {

  while (((INB(I8042_COMMAND)) & 1) == 0)
      ;

  char c = INB (0x60);

  write_text_vga ("x");
}

/* extern void refresh_ps2_controller () {
  while (!((INB (I8042_COMMAND)) & 1))
    continue;
  u8 scan_code = get_scan_code ();
  if (get_type () == KEYRELEASED)
  {
    keyboard_new_event = TRUE;
    keyboard_lastkeypressed = scan_code;
  }
} */

