#include "pm.h"

#define NULL_SEGMENT 0
#define KERNEL_CODE_SEGMENT 1
#define KERNEL_DATA_SEGMENT 2
#define USER_CODE_SEGMENT 3
#define USER_DATA_SEGMENT 4

typedef struct gdt_entry_s {
  u16 limit0_15;
  u16 base0_15;
  u8 base16_23;
  u8 type: 4;
  u8 dtype: 1;
  u8 dpl: 2;
  u8 present:1;
  u8 limit16_19: 4;
  u8 avl: 1;
  u8 l: 1;
  u8 dsize: 1;
  u8 granularity: 1;
  u8 base24_31;
} __attribute__((packed)) gdt_entry_t;

#define MAKE_SELECTOR(index, ti, rpl) \
  ( \
    (index << 3) | \
    ((ti & 0x1) << 2) | \
    (rpl & 0x3) \
  ) 

static void load_segments () {
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

#define ADD_GDT_ENTRY(base,limit,privilege,code) \
  ((gdt_entry_t){ \
    .limit0_15 = limit & 0xffff, \
    .base0_15 = base & 0xffff, \
    .base16_23 = (base & 0xff0000) >> 16, \
    .type = ((code)? 0xb : 0x3), \
    .dtype = 1, \
    .dpl = (privilege & 0x3), \
    .present = 1, \
    .limit16_19 = (limit & 0xf0000) >> 16, \
    .avl = 0, \
    .l = 0, \
    .dsize = 1, \
    .granularity = 1, \
    .base24_31 = (base & 0xff00000) >> 24 \
   })

typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) gdt_t;


static void load_gdt () {

  struct gdt_entry_s gdt[5];
  gdt[NULL_SEGMENT] = (struct gdt_entry_s){0,};
  gdt[KERNEL_CODE_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 0, 1);
  gdt[KERNEL_DATA_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 0, 0); 
  gdt[USER_CODE_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 3, 1);
  gdt[USER_DATA_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 3, 0); 

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

  __asm__ volatile (
    "movl %%cr0, %%eax\n\
    orl $1, %%eax\n\
    movl %%eax, %%cr0\n"
    :
    :
    : "eax"
    );

  load_segments ();
}
