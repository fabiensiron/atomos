#include "i8042.h"

static char sc_table[] = 
  {
    SC_NULL, SC_NULL,  // 0x0
    '1','2','3','4','5','6','7','8','9','0', // 0x1
    '-','=',SC_NULL,SC_NULL,  // 0x0c
    'q','w','e','r','t','y','u','i','o','p', // 0x10
    '[',']',SC_ENTER,SC_NULL, // 0x1A
    'a','s','d','f','g','h','j','k','l', // 0x1e
    ';','\'','`',SC_NULL,'\\', //0x27
    'z','x','c','v','b','n','m', // 0x2c
    ',','.','/',SC_NULL,'*',SC_NULL,' ',SC_NULL, //0x33
    SC_NULL,SC_NULL,SC_NULL,SC_NULL,
    SC_NULL,SC_NULL,SC_NULL,SC_NULL, // 0x3B
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

static char scan_to_ascii (u8 sc_, u8 we_) {
  static u8 write_enable = 0;
  if ((we_ == W_ENABLE) || 
      (we_ == W_DISABLE)) {
    write_enable = we_;
    return 0;
  } else if ((we_ != W_NULL) || 
      (write_enable != W_ENABLE))
    return 0;

  u8 input = sc_table[sc_];
    
  if ((input != SC_ENTER) && (input_buffer_cursor == 77)) return 0;
  
  if (input != SC_NULL) {
    input_buffer [input_buffer_cursor % 80] = input;
    (input_buffer_cursor)++;
    if (input != SC_ENTER)
      kprintf ("%c", input_buffer [(input_buffer_cursor)-1]);
  }

  return input;
}

/* just for test */

extern void refresh_ps2_controller () {
  static u8 ignore = 0;

  while (((INB(I8042_COMMAND)) & 1) == 0)
      ;

  u8 c = INB (0x60);

  if (ignore) {
    ignore = 0;
    return;
  }
  if (c == 0xE0) {
    ignore = 1;
    return;
  }

  if (get_type(c) != KEYRELEASED)
    return;
  u8 sc = get_scan_code (c);
  scan_to_ascii (sc, W_NULL);
}

extern void wait_input (char* buffer) {
  for (int i = 0; i< 80; i++)
    input_buffer[i] = 0;

  input_buffer_cursor = 0;
  scan_to_ascii (0,W_ENABLE);


  u8 input = 0x0;
  while (((input_buffer_cursor) == 0) ||
        (input_buffer [(input_buffer_cursor) -1] 
         != SC_ENTER))
    ;
  scan_to_ascii (0,W_DISABLE);
      /*||
    //    (input_buffer[input_buffer_cursor-1] 
      //  == SC_ENTER)*/ /* wait input */
    // ;// kprintf ("%c", input_buffer[input_buffer_cursor]);
    
    memcpy (buffer, input_buffer, input_buffer_cursor-1);
    buffer [input_buffer_cursor-1] = '\0';

//    for (int i = 0; buffer[i] != '\0'; i++) 
  //    kprintf ("%c:%x", buffer[i], buffer[i]);
}


