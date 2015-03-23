#ifndef _PM_H
#define _PM_H

#include <include/kernel.h>
#include <drivers/vga_text.h>

#define NULL_SEGMENT 0
#define KERNEL_CODE_SEGMENT 1
#define KERNEL_DATA_SEGMENT 2
#define USER_CODE_SEGMENT 3
#define USER_DATA_SEGMENT 4

typedef struct {
  /* first 32 bits */
  u16 limit0_15;
  u16 base0_15;
  /* second 32 bits */
  u8 base16_23;
  u8 type: 4; /* read/write/execute etc... */
  u8 dtype: 1; /* 0 -> system; 1 -> code/data */
  u8 dpl: 2; /* privilege level (ring) */
  u8 present: 1; /* present */
  u8 limit16_19: 4; 
  u8 avl: 1; /* available for use by syst soft */
  u8 l: 1; /* 64 bit */
  u8 defaut_size: 1; /* 0 -> 16 bit; 1 -> 32 bit */
  u8 granularity: 1; /* if 1 then numb of 4kb page */
  u8 base24_31; 
} __attribute__((packed)) gdt_entry_t;

#define ADD_GDT_ENTRY(base, limit, privilege, code) \
    ((gdt_entry_t){   \
        .limit0_15 = limit & 0xffff,  \
        .base0_15  = base & 0xffff, \
        .base16_23 = (base & 0xff0000) >> 16, \
        .type = ((code)? 0xb : 0x3),   \
        .dtype = 1, \
        .dpl = (privilege & 0x3), \
        .present = 1, \
        .limit16_19 = (limit & 0xf0000)>> 16, \
        .avl = 0, \
        .l = 0, \
        .defaut_size = 1, \
        .granularity = 0, \
        .base24_31 = (base & 0xff000000) >> 24 \
    })            
                                                

typedef struct {
  u16 limit; 
  u32 base;
} __attribute__((packed)) gdt_t;

/* ti -> table indicator 0 -> gdt; 1 -> ldt */
/* rpl -> ring */

#define MAKE_SELECTOR(index, ti, rpl) \
  ( \
    (index << 3) | \
    (ti << 2) | \
    (rpl) \
  )

extern void switch_to_pm ();



#endif /* _PM_H */
