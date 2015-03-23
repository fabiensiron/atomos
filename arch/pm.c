#include "pm.h"

static void load_segments () {
  write_text_vga ("done\n");
  __asm__ volatile (
    "ljmp %0, $1f \n\
    1: \n\
    movw %1, %%ax \n\
    movw %%ax, %%ss \n\
    movw %%ax, %%ds \n"
    :
    : "i"(MAKE_SELECTOR (KERNEL_CODE_SEGMENT, 0, 0)), 
      "i"(MAKE_SELECTOR (KERNEL_DATA_SEGMENT, 0, 0))
    :"eax"
    );
}

static void load_gdt () {

  gdt_entry_t gdt[3];
  gdt[NULL_SEGMENT] = (gdt_entry_t){0,};
  gdt[KERNEL_CODE_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 0, 1);
  gdt[KERNEL_DATA_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 0, 0);
 /* gdt[USER_CODE_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 3, 1);
  gdt[USER_DATA_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 3, 0); 
*/
  gdt_t gdt_desc;
  gdt_desc.limit = sizeof (gdt) -1;
  gdt_desc.base = (u32)gdt;
  
  __asm__ volatile (
    "lgdt %0\n"
    :
    : "m" (gdt_desc)
    : "memory"
    );
}

extern void switch_to_pm () {
  load_gdt ();
  write_text_vga ("done\n");
  
  __asm__ volatile (
  "movl %%cr0, %%eax\n\
  orl $1, %%eax\n\
  movl %%eax, %%cr0\n"
  :
  :
  :"eax"
  ); 
  write_text_vga ("done\n");
  load_segments ();
}
