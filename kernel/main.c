#include <arch/multiboot.h>
#include <arch/pm.h>
#include <arch/irq.h>
#include <arch/idt.h>
#include <arch/exception.h>
#include <drivers/vga_text.h>
#include <drivers/i8259.h>
#include <arch/ioport.h>
#include <include/kernel.h>
#include <include/stdio.h>
#include <include/string.h>


void kernel_main (unsigned long magic, multiboot_info_t* info) {
  set_bg_color (BLACK); 
  set_fg_color (WHITE);

  clear_screen ();

  if (magic == MULTIBOOT_BOOTLOADER_MAGIC) {
    kprintf ("[000] boot with grub\n");
    kprintf ("[001] flags: %x\n", info->flags);
    kprintf ("[002] memory lower: %x\n", info->mem_lower);
    kprintf ("[003] memory upper: %x\n", info->mem_upper);
    kprintf ("[004] boot device: %x\n", info->boot_device);
    kprintf ("[005] command line: %x\n", info->cmdline);
    kprintf ("[006] modules number: %x\n", info->mods_count);
    kprintf ("[007] modules address: %x\n", info->mods_addr);
    kprintf ("[008] mmap length: %x\n", info->mmap_length);
    kprintf ("[009] mmap address: %x\n", info->mmap_addr);
    kprintf ("[010] drives length: %x\n", info->drives_length);
    kprintf ("[011] drives address: %x\n", info->drives_addr);
  }

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
 //
  

//  boot_message (); 
  
  //kout_init();
  //

  for (;;)
    continue;
}
