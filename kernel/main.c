#include <arch/multiboot.h>
#include <arch/pm.h>
#include <arch/irq.h>
#include <arch/idt.h>
#include <arch/exception.h>
#include <drivers/vga_text.h>
#include <drivers/i8259.h>
#include <arch/ioport.h>
#include <include/kernel.h>
#include <include/string.h>


void kernel_main (unsigned long magic, multiboot_info_t* info) {
  set_bg_color (BLACK); 
  set_fg_color (WHITE);

  clear_screen ();

  /* set 32-bits intel protected mode */
  switch_to_pm ();

  /* init the i8259 (interrupt controller) */
  pic_init ();

  /* set-up the idt */
  load_idt ();

  /* init exceptions */
  exception_init ();

  /* enable irq */
  init_irq ();

  /* set interrupts up */
  STI;

  // test trap 
  // int a = 4 / 0;

 // write_text_vga ("\n");

 boot_message (); 

  for (;;)
    continue;
}
