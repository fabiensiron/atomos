#include "vga_text.h"

static void write_char (char c) {
  u16* addr = (u16*)TEXT_FRAMEBUFFER_START + 2*NB_ROWS*cursor.r +
      2*NB_COLUMNS*cursor.c;
  switch (c) {
    case '\n':
      ++cursor.r;
      break;
    case '\r':
      cursor.c = 0;    
      break;
    case '\t':
      cursor.c += 3;
      break;
    case '\b':
      --cursor.c;
      break;
    default:
      *addr = (text_color.bg << 4 + text_color.fg)<<8 + c;  
      break;
  }
}

extern void write_text_vga (char* str) {
  int i;
  for (i = 0; i!= '\0'; i++)
    write_char (str[i]);
}

extern void clear_screen () {
  int i;
  for (int i =TEXT_FRAMEBUFFER_START; i < TEXT_FRAMEBUFFER_END; i++)
  {
    u8* addr = (u8*)i;
    *addr = 0;
  }
}
