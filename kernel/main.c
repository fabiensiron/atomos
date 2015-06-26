#include <arch/multiboot.h>
#include <arch/pm.h>
#include <arch/interrupt.h>
#include <drivers/vga_text.h>
#include <drivers/i8259.h>
#include <arch/ioport.h>
#include <include/kernel.h>
#include <include/string.h>


void kernel_main (unsigned long magic, multiboot_info_t* info) {
  set_bg_color (BLACK); 
  set_fg_color (WHITE);

  clear_screen ();

  write_text_vga ("load gdt...\n");
 switch_to_pm ();
 // load_gdt ();
  write_text_vga ("gdt loaded!\n"); 

  write_text_vga ("load idt...\n");
  init_interrupts ();
  write_text_vga ("idt loaded!\n");

/*  write_text_vga ("init pic...\n");
  pic_init ();
  write_text_vga ("pic init!\n");
*/
 // STI;

  write_text_vga ("set interrupts\n");

  // test trap 
  int a = 4 / 0;

  write_text_vga ("\n");

  boot_message (); 
 /* 
  panic (""); */

  for (;;)
    continue;
}
