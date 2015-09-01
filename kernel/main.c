#include <arch/multiboot.h>
#include <arch/pm.h>
#include <arch/irq.h>
#include <arch/idt.h>
#include <arch/exception.h>
#include <drivers/vga_text.h>
#include <drivers/serial.h>
#include <drivers/i8259.h>
#include <drivers/i8253.h>
#include <drivers/mbr.h>
#include <arch/ioport.h>
#include <include/kernel.h>
#include <include/time.h>
#include <include/stdio.h>
#include <include/string.h>
#include <include/elf_loader.h>
#include <include/task.h>
#include <include/log.h>
#include <include/mem.h>
#include <include/stddef.h>
#include <include/config.h>
#include <include/ext2.h>

void kernel_main (unsigned long magic, multiboot_info_t* info) 
{
  set_bg_color (BLACK); 
  set_fg_color (WHITE);

  clear_screen ();

  write_text_vga ("kernel is booting...\n");

  if (magic == MULTIBOOT_BOOTLOADER_MAGIC) 
    {
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
  
  if (info->drives_length != 0)
    {
      drive_t *drive_info = (drive_t *)info->drives_addr;
      klog ("found multiboot drive info!", NULL, STATE_NOTHING);
      klog ("drive size",&drive_info->size,STATE_NOTHING);
      klog ("drive number",&drive_info->drive_number,STATE_NOTHING | SIZE_U8);
      if (drive_info->drive_mode == DRIVE_MODE_CHS)
        klog ("drive mode CHS",NULL,STATE_NOTHING);
      else
        klog ("drive mode LBA",NULL,STATE_NOTHING);
      klog ("drive cylinders",&drive_info->drive_cylinders,STATE_NOTHING | SIZE_U16);
      klog ("drive heads",&drive_info->drive_heads,STATE_NOTHING | SIZE_U8);
      klog ("drive sectors",&drive_info->drive_sectors,STATE_NOTHING | SIZE_U8);
      klog ("drive port 1",&drive_info->drive_port1,STATE_NOTHING | SIZE_U8);
      klog ("drive port 2",&drive_info->drive_port2,STATE_NOTHING | SIZE_U8);
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

  pit_init ();
  klog ("init timer", NULL, STATE_OK);

  serial_init (); 
  klog ("init serial", NULL, STATE_OK);

  /* set interrupts up */

  STI;
  klog ("enable hardware interrupt (STI)", NULL, STATE_OK);


  /* put kernel brk */

  mem_init (); 
  klog ("init kernel memory", NULL, STATE_OK);

  mbr_dump_info ();
  if (mbr_check_boot_integrity() == -1)
    panic ("no boot sector found !");

  mbr_show_info ();
  struct mbr_entry *part_info = mbr_find_bootable ();

  ext2_init (0, part_info->lba_start);
  if (ext2_check_integrity() == -1)
    panic ("Unable to read ext2");

  klog ("init filesystem", NULL, STATE_OK);
  
  
  u32 sys_nmb = 0x80;
  klog ("system call", &sys_nmb, STATE_NOTHING);



#ifdef USERLAND 


  if (magic == MULTIBOOT_BOOTLOADER_MAGIC && 
      info->mods_count == 1) {
    load_elf((u32)info->mods_addr);
    klog ("load user binary (ELF)", NULL, STATE_OK);

    set_syscall_handler (sys_nmb); 
    klog ("init syscall at port", &sys_nmb, STATE_OK);

    klog ("jump to userland", NULL, STATE_OK);
    u32 loc_entry = (u32)entry;
    klog ("task entry",&loc_entry, STATE_NOTHING);
    clear_screen ();
    load_task (loc_entry);
  } else {
    klog ("load user binary (ELF)", NULL, STATE_FAILED);
    klog ("init syscall at port", &sys_nmb, STATE_FAILED);
    klog ("jump to userland", NULL, STATE_FAILED);
  }
#endif

//  klog ("done...",NULL,STATE_NOTHING);
  clear_screen ();
  write_text_vga ("done...\n");

  for (;;)
    continue;
}
