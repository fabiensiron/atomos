#include "pm.h"

static void load_gdt () {

  gdt_entry_t gdt[5];
  gdt[NULL_SEGMENT] = (gdt_entry_t){0,};
  gdt[KERNEL_CODE_SEGMENT] =  ADD_GDT_ENTRY (0, 0xfffff, 0, 1);
  gdt[KERNEL_DATA_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 0, 0);
  gdt[USER_CODE_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 3, 1);
  gdt[USER_DATA_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 3, 0); 

  gdt_t gdt_desc = (gdt_t){
    .limit = (sizeof (gdt) - 1),
    .base = gdt
  };
  
  __asm__ volatile (
    "lgdt %0\n"
    :
    :"m" (gdt_desc)
    : "memory"
    );
}

extern void switch_to_pm () {
  load_gdt ();

}
