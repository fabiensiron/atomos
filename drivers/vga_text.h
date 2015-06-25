#ifndef _VGA_TEXT_H
#define _VGA_TEXT_H

#include <include/kernel.h>

#define TEXT_FRAMEBUFFER_START 0xB8000
#define TEXT_FRAMEBUFFER_END   0xc0000
#define TEXT_FRAMEBUFFER_NPB   16 

static struct {
  int c; 
  int r;
} cursor = {0,0};

typedef enum {
  BLACK   = 0,
  BLUE    = 1,
  GREEN,
  CYAN,
  RED,
  MAGENTA,
  BROWN,
  WHITE,
  GRAY,
  LIGHT_BLUE,
  LIGHT_GREEN,
  LIGHT_CYAN,
  LIGHT_RED,
  LIGHT_MAGENTA,
  YELLOW,
  LIGHT_WHITE
} text_color_e;

static struct {
  text_color_e bg;
  text_color_e fg;
} text_color = {BLACK, WHITE};

#define NB_ROWS 25
#define NB_COLUMNS 80

// static void write_char (char c);
// static void scroll_down ();

extern void write_text_vga (char* str);
extern void set_cursor (u64 r, u64 c);
extern void clear_screen ();
extern void fill_screen (text_color_e bg_);
extern void set_fg_color (text_color_e);
extern void set_bg_color (text_color_e);
extern void boot_message ();


#endif /* _VGA_TEXT_H */
