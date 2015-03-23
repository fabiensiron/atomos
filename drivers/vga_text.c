#include "vga_text.h"

static void write_char (char c_) {
  u8* addr = (u8*)TEXT_FRAMEBUFFER_START + 2*cursor.r*NB_COLUMNS +cursor.c*2;
  switch (c_) {
    case '\n':
      ++cursor.r;
      cursor.c = 0;
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
      *addr = c_;
      *(addr+1) = (u8)(text_color.bg << 4) + text_color.fg;  
      ++cursor.c;
      break;
  }
}

extern void write_text_vga (char* str) {
  int i;
  for (i = 0; str[i] != '\0'; i++)
    write_char (str[i]); 
}

extern void clear_screen () {
  int i;
  for (int i =TEXT_FRAMEBUFFER_START; i < TEXT_FRAMEBUFFER_END; i+=2)
  {
    u8* addr = (u8*)i;
    *addr = ' ';
    *(addr+1) = (u8)(text_color.bg << 4) + text_color.fg;
  }
  cursor.c = 0;
  cursor.r = 0;
}

extern void set_fg_color (text_color_e c_) {text_color.fg = c_;}
extern void set_bg_color (text_color_e c_) {text_color.bg = c_;}
extern void set_cursor (u64 r_, u64 c_) {cursor.c = c_; cursor.r = c_;};
extern void fill_screen () {
  /* TODO */
}

extern void boot_message () {
  write_text_vga ("Welcome in atomOS!!\n\n");
  write_text_vga ("Don't worry, it's only a begining, this project is still under construction.\n");
  write_text_vga ("I hope you will follow our project.\n\n");
  write_text_vga ("AUTHORS: \n");
  write_text_vga ("\t# Fabien 'Saruta' Siron\n");
  write_text_vga ("\t# Francois 'Hellzy' Mazeau\n\n");
  write_text_vga ("LOADING...\n");
}
