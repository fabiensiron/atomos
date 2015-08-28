#include <include/syscall.h>
#include <include/mem.h>
#include <arch/pm.h>

static u32 sys_sbrk (u32 offset_) {
  u32 base = (u32)brk;
  brk += offset_;

  return base;
}

static void sys_write (char* arg) {
  kprintf ("%s", arg);
}

static u32 sys_read (u8* buffer) {
  return wait_input (buffer);   
}

#define RETURN(val_,ptr_) (ptr_[13] = val_)

extern void syscall (u32 num_, u32 arg_) {
  u32* ptr;
  __asm__ volatile (
    "mov %%ebp, %0\n"
    :"=m"(ptr)
    :
    );

  switch (num_) {
    case SYS_WRITE:
      sys_write ((void*)(arg_+USER_BASE));  
      break;
    case SYS_READ:{
      u32 count = sys_read ((void*)(arg_+USER_BASE));
      RETURN(count,ptr);
      }break;
    case SYS_SBRK:{
      u32 addr = ksbrk (arg_);
      RETURN(addr,ptr);
      }break;
    default:
      kprintf ("undefined syscall...\n");
      RETURN(-1,ptr);
      break;
  }
  return;
}
