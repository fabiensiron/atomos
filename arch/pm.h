#ifndef _PM_H
#define _PM_H

#include <include/kernel.h>
#include <drivers/vga_text.h>

#define USER_BASE 0x20000

#define NULL_SEGMENT 0
#define KERNEL_CODE_SEGMENT 1
#define KERNEL_DATA_SEGMENT 2
#define USER_CODE_SEGMENT 3
#define USER_DATA_SEGMENT 4
#define TSS_SEGMENT 5

extern void switch_to_pm ();
extern void reset_segment (int num_, u32 min_, u32 max_,
    u8 ring_, u8 code_);

#endif /* _PM_H */
