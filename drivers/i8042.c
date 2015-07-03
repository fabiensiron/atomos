#include "i8042.h"

static u8 get_type ();
static u8 get_scan_code ();

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

static u8 get_type () {
  return ((INB(I8042_DATA)) & 0x80)?KEYPRESSED:KEYRELEASED;
}

static u8 get_scan_code () {
  return (INB (I8042_DATA)) & 0x7f; 
}
