#include <include/kernel.h>
#include <drivers/vga_text.h>

void panic (const char* msg) 
{
  CLI;

  fill_screen (BLUE);

  set_bg_color (BLUE);

  write_text_vga ("");
  write_text_vga ("Kernel panic : ");
  write_text_vga (msg);

  for (;;)
    continue;
}
