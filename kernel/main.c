#include <arch/multiboot.h>
#include <drivers/vga_text.h>

void kernel_main (unsigned long magic, multiboot_info_t* info) {
  char* str = ("welcome \n in \n \n \n \n \n ATOMOS !!!");

  clear_screen ();

  write_text_vga (str);

  for (;;)
    continue;
}
