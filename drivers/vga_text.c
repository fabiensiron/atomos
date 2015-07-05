#include "vga_text.h"

static void update_cursor (int r_, int c_) {
  int position = r_ * 80 + c_;
  
  OUTB(14, 0x3D4);
  OUTB(position >> 8, 0x3D5);

  OUTB(15, 0x3D4);
  OUTB(position, 0x3D5);
}

extern void scroll_down () {
  int offset_ = 2*NB_COLUMNS;
  u8 next;
  for (int r_ = 1; r_ <= NB_ROWS; r_++) {
    for (int c_ = 0; c_ < NB_COLUMNS; c_++) {
      u8* addr = (u8*)TEXT_FRAMEBUFFER_START + 2*r_*NB_COLUMNS + c_*2;  
      next = ((u32)addr)<TEXT_FRAMEBUFFER_END?*addr:' ';
      *(addr-offset_) = next;
    }
  }
  cursor.r--;
  update_cursor (cursor.r, cursor.c);
}

static void write_char (char c_) {
  cursor.r = cursor.r + cursor.c / NB_COLUMNS;
  cursor.c = cursor.c % NB_COLUMNS;

  u8* addr = (u8*)TEXT_FRAMEBUFFER_START + 2*cursor.r*NB_COLUMNS +cursor.c*2;
  if ((u32)addr >= TEXT_FRAMEBUFFER_END) 
  {
    scroll_down();
    addr = (u8*)TEXT_FRAMEBUFFER_START + 2*cursor.r*NB_COLUMNS +cursor.c*2;
  }

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
  update_cursor (cursor.r, cursor.c);
}

extern void write_text_vga (char* str) {
  int i;
  for (i = 0; str[i] != '\0'; i++){
    write_char (str[i]); 
  }
}

extern void clear_screen () {
  for (int i =TEXT_FRAMEBUFFER_START; i < TEXT_FRAMEBUFFER_END; i+=2)
  {
    u8* addr = (u8*)i;
    *addr = ' ';
    *(addr+1) = (u8)(text_color.bg << 4) + text_color.fg;
  }
  cursor.c = 0;
  cursor.r = 0;
  update_cursor (cursor.r, cursor.c);
}

extern void set_fg_color (text_color_e c_) {text_color.fg = c_;}
extern void set_bg_color (text_color_e c_) {text_color.bg = c_;}
extern void set_cursor (u64 r_, u64 c_) {cursor.c = c_; cursor.r = c_;};

extern void fill_screen (text_color_e bg_) {
  for (int i =TEXT_FRAMEBUFFER_START; i < TEXT_FRAMEBUFFER_END; i+=2)
  {
    u8* addr = (u8*)i;
    *addr = ' ';
    *(addr+1) = (u8)(bg_ << 4) + text_color.fg;
  }
  text_color.bg = bg_;
  cursor.c = 0;
  cursor.r = 0;
  update_cursor (cursor.r, cursor.c);
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
