#include <include/kernel.h>
#include <include/syscall.h>
#include <arch/pm.h>

static void actualize_seg (u32 new_brk_) {
//  reset_segment (USER_DATA_SEGMENT, (u32)USER_BASE,
  //    (u32)(new_brk_+USER_BASE), 3,0);
}

extern u32 sys_sbrk (u32 offset_) {
  u32 base = (u32)brk;
  brk += offset_;

//  actualize_seg ((u32)brk);

  return base;
}
