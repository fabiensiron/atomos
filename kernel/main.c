#include <arch/multiboot.h>
#include <drivers/vga_text.h>

void kernel_main (unsigned long magic, multiboot_info_t* info) {
  set_bg_color (BLUE); 
  set_fg_color (WHITE);

  clear_screen ();

  boot_message ();
  

  for (;;)
    continue;
}
