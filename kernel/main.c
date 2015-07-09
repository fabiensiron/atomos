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
#include <include/elf_loader.h>

static void fake_sleep () {
  for (int i = 0; i<10000000; i++)
    ;
}

void kernel_main (unsigned long magic, multiboot_info_t* info) {
  set_bg_color (BLACK); 
  set_fg_color (WHITE);

  clear_screen ();

  if (magic == MULTIBOOT_BOOTLOADER_MAGIC) {
    kprintf ("[000] boot with grub\n");
    fake_sleep ();
    kprintf ("[001] flags: %x\n", info->flags);
    fake_sleep ();
    kprintf ("[002] memory lower: %x\n", info->mem_lower);
    fake_sleep ();
    kprintf ("[003] memory upper: %x\n", info->mem_upper);
    fake_sleep ();
    kprintf ("[004] boot device: %x\n", info->boot_device);
    fake_sleep ();
    kprintf ("[005] command line: %s\n", info->cmdline);
    fake_sleep ();
    kprintf ("[006] modules number: %x\n", info->mods_count);
    fake_sleep ();
    kprintf ("[007] modules address: %x\n", info->mods_addr);
    fake_sleep ();
    kprintf ("[008] mmap length: %x\n", info->mmap_length);
    fake_sleep ();
    kprintf ("[009] mmap address: %x\n", info->mmap_addr);
    fake_sleep ();
    kprintf ("[010] drives length: %x\n", info->drives_length);
    fake_sleep ();
    kprintf ("[011] drives address: %x\n", info->drives_addr);
    fake_sleep ();
  }

  /* set 32-bits intel protected mode */

  kprintf ("[012] load gdt");
  switch_to_pm ();
  set_fg_color (GREEN);
  kprintf ("\t\t\t\t\t\t\t\t\tOK\n");
  set_fg_color (WHITE);
    fake_sleep ();

  kprintf ("[013] jump to 32-bits protected");
  set_fg_color (GREEN);
  kprintf ("\t\t\t OK\n");
  set_fg_color (WHITE);
    fake_sleep ();

  /* init the i8259 (interrupt controller) */

  kprintf ("[014] init i8259 interrupt controller");
  pic_init ();
  set_fg_color (GREEN);
  kprintf ("\t OK\n");
  set_fg_color (WHITE);
    fake_sleep ();

  /* set-up the idt */

  kprintf ("[015] init interrupt table");
  load_idt ();
  set_fg_color (GREEN);
  kprintf ("\t\t\t\t   OK\n");
  set_fg_color (WHITE);
    fake_sleep ();

  /* init exceptions */

  kprintf ("[016] init exceptions");
  exception_init ();
  set_fg_color (GREEN);
  kprintf ("\t\t\t\t\t\t  OK\n");
  set_fg_color (WHITE);
    fake_sleep ();

  /* enable irq */

  kprintf ("[017] init hardware interrupt");
  init_irq ();
  set_fg_color (GREEN);
  kprintf ("\t\t\t\tOK\n");
  set_fg_color (WHITE);
    fake_sleep ();

  /* set interrupts up */

  kprintf ("[018] set interrupt");
  STI;
  set_fg_color (GREEN);
  kprintf ("\t\t\t\t\t\t\t OK\n");
  set_fg_color (WHITE);
    fake_sleep ();

  
  kprintf ("[019] load user binary (elf)");
  if (magic == MULTIBOOT_BOOTLOADER_MAGIC && 
      info->mods_count == 1) {
    load_elf((u32)info->mods_addr);
    set_fg_color (GREEN);
    kprintf ("\t\t\t\t OK\n");
  } else {
    set_fg_color (RED);
    kprintf ("\t\t\t\t FAILED\n");
    set_fg_color (WHITE);
  }
    set_fg_color (WHITE);
      fake_sleep ();

  set_fg_color (RED);

  kprintf ("\n====================================\n");
  kprintf ("        Welcome in atomOS !!\n");
  kprintf ("====================================\n\n");

  set_fg_color (WHITE);
  kprintf ("$");

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
