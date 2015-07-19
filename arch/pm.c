#include "pm.h"

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
} __attribute__((packed,aligned(8))) gdt_entry_t;


typedef struct tss_entry_s {
  u16 previous_task, unusedt;
  u32 esp0;
  u16 ss0, unused0;
  u32 esp1;
  u16 ss1, unused1;
  u32 esp2;
  u16 ss2, unused2;
  u32 cr3;
  u32 eip,eflags;
  u32 eax,ecx,edx,ebx,esp,ebp,esi,edi;
  u16 es, unused_es;
  u16 cs, unused_cs;
  u16 ss, unused_ss;
  u16 ds, unused_ds;
  u16 fs, unused_fs;
  u16 gs, unused_gs;
  u16 ldt_selector, unused_ldt;
  u16 debug_flag, io_map;
} __attribute__((packed,aligned(8))) tss_entry_t;

#define MAKE_SELECTOR(index, ti, rpl) \
  ( \
    (index << 3) | \
    (((ti)?1:0) << 2) | \
    (rpl & 0x3) \
  ) 

static void load_segments () {
  __asm__ volatile (
    "movw %0, %%ax \n\
    movw %%ax, %%ds \n \
    movw %%ax, %%es \n \
    movw %%ax, %%fs \n \
    movw %%ax, %%gs \n \
    movw %%ax, %%ss \n\
    ljmp %1, $1f \n\
    1:"
    :
    : "i"(MAKE_SELECTOR(KERNEL_DATA_SEGMENT, 0, 0)), 
      "i"(MAKE_SELECTOR(KERNEL_CODE_SEGMENT, 0, 0))
    :"eax"
    );
}

#define ADD_GDT_ENTRY(base,limit,privilege,code) \
  ((gdt_entry_t){ \
    .limit0_15 = limit & 0xffff, \
    .base0_15 = base & 0xffff, \
    .base16_23 = (base >> 16) & 0xff, \
    .type = ((code)? 0xa : 0x2), \
    .dtype = 1, \
    .dpl = (privilege & 0x3), \
    .present = 1, \
    .limit16_19 = (limit >> 16) & 0xf, \
    .avl = 0, \
    .l = 0, \
    .dsize = 1, \
    .granularity = 1, \
    .base24_31 = (base >> 24) & 0xff \
   })

#define ADD_TSS_ENTRY(base,limit) \
  ((gdt_entry_t){ \
    .limit0_15 = limit & 0xffff, \
    .base0_15 = base & 0xffff, \
    .base16_23 = (base >> 16) & 0xff, \
    .type = 9, \
    .dtype = 0, \
    .dpl = 0x3, \
    .present = 1, \
    .limit16_19 = (limit >> 16) & 0xf, \
    .avl = 0, \
    .l = 0, \
    .dsize = 0, \
    .granularity = 0, \
    .base24_31 = (base >> 24) & 0xff \
   })

typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed,aligned(8))) gdt_t;

struct tss_entry_s tss;
struct gdt_entry_s gdt[6];

static void load_gdt () {

  /* init tss */
  tss.debug_flag = 0;
  tss.io_map = 0;
  tss.ss0 = MAKE_SELECTOR(KERNEL_DATA_SEGMENT,0,0);
  tss.esp0 = 0x20000;

  /* init gdt */

  gdt[NULL_SEGMENT] = (struct gdt_entry_s){0,};

  gdt[KERNEL_CODE_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 0, 1);
  gdt[KERNEL_DATA_SEGMENT] = ADD_GDT_ENTRY (0, 0xfffff, 0, 0); 
  gdt[USER_CODE_SEGMENT] = ADD_GDT_ENTRY (USER_BASE, 0xfffff, 3, 1);
  gdt[USER_DATA_SEGMENT] = ADD_GDT_ENTRY (USER_BASE, 0xfffff, 3, 0); 
  gdt[TSS_SEGMENT] = ADD_TSS_ENTRY ((u32)&tss, 0x67);

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

extern void reset_segment (int num_, u32 min_, u32 max_, 
    u8 ring_, u8 code_) {
  gdt[num_] = ADD_GDT_ENTRY (min_,max_,ring_,code_);
}

static void load_tss () {
  __asm__ volatile (
    "movw $0x28, %%ax \n\
     ltr %%ax\n\
     movw %%ss, %0 \n\
     movl %%esp, %1\n"
      : "=m"(tss.ss0) ,"=m"(tss.esp0)
      :
      :
      );
}

extern void switch_to_pm () {
    __asm__ volatile (
    "movl %%cr0, %%eax\n\
    orl $1, %%eax\n\
    movl %%eax, %%cr0\n"
    :
    :
    : "eax"
    ); 
  load_gdt ();
/* 
*/
  load_segments ();
  load_tss();
}
