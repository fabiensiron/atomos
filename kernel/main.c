#include <arch/multiboot.h>

void kernel_main (unsigned long magic, multiboot_info_t* info) {




  loop:
    goto loop;

  return;
}
