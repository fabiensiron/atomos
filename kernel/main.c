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
#include <include/task.h>
#include <include/log.h>

static void fake_sleep () {
  for (int i = 0; i<10000000; i++)
    ;
}

void kernel_main (unsigned long magic, multiboot_info_t* info) {
  set_bg_color (BLACK); 
  set_fg_color (WHITE);

  clear_screen ();

  if (magic == MULTIBOOT_BOOTLOADER_MAGIC) {
    klog ("boot with grub", NULL, STATE_NOTHING);
    klog ("flags", &info->flags, STATE_NOTHING);
    klog ("memory lower", &info->mem_lower, STATE_NOTHING);
    klog ("memory upper", &info->mem_upper, STATE_NOTHING);
    klog ("boot device", &info->boot_device, STATE_NOTHING);
    klog ("command line", (u32*)info->cmdline, 
        STATE_NOTHING | TYPE_STRING);
    klog ("modules number", &info->mods_count, 
        STATE_NOTHING | TYPE_UINT);
    klog ("modules address", &info->mods_addr, STATE_NOTHING);
    klog ("mmap length", &info->mmap_length, STATE_NOTHING);
    klog ("mmap address", &info->mmap_addr, STATE_NOTHING);
    klog ("drives length", &info->drives_length, STATE_NOTHING);
    klog ("drives address", &info->drives_addr, STATE_NOTHING);
  }



  /* set 32-bits intel protected mode */

  switch_to_pm ();
  klog ("load general description table (GDT)", NULL, STATE_OK);
  klog ("load intel 32 protected mode", NULL, STATE_OK);
  klog ("init task state segment (TSS)", NULL, STATE_OK);

  /* init the i8259 (interrupt controller) */

  pic_init ();
  klog ("init programmable interrupt controller (i8259)"
      , NULL, STATE_OK);

  /* set-up the idt */

  load_idt ();
  klog ("init interrupt descriptor table (IDT)", NULL, STATE_OK);

  /* init exceptions */

  exception_init ();
  klog ("init exceptions", NULL, STATE_OK);


  /* enable irq */

  init_irq ();
  klog ("init hardware interrupt (IRQ)", NULL, STATE_OK);

  /* set interrupts up */

  STI;
  klog ("enable hardware interrupt (STI)", NULL, STATE_OK);
  
  u32 sys_nmb = 0x80;

  if (magic == MULTIBOOT_BOOTLOADER_MAGIC && 
      info->mods_count == 1) {
    load_elf((u32)info->mods_addr);
    klog ("load user binary (ELF)", NULL, STATE_OK);

    set_syscall_handler (sys_nmb); 
    klog ("init syscall at port", &sys_nmb, STATE_OK);

    klog ("jump to userland", NULL, STATE_OK);
    load_task ();
  } else {
    klog ("load user binary (ELF)", NULL, STATE_FAILED);
    klog ("init syscall at port", &sys_nmb, STATE_FAILED);
    klog ("jump to userland", NULL, STATE_FAILED);
  }

  /*  
  set_fg_color (RED);

  kprintf ("\n====================================\n");
  kprintf ("        Welcome in atomOS !!\n");
  kprintf ("====================================\n\n");

  set_fg_color (WHITE);
  kprintf ("$");
*/
  // test trap 
  // int a = 4 / 0;

  //kout_init(); //TODO

  for (;;)
    continue;
}
