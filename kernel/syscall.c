#include <include/syscall.h>
#include <arch/pm.h>

static void sys_write (char* arg) {
  kprintf ("%s", arg);
}

static void sys_read (u8* buffer) {
  wait_input (buffer);   
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
    case SYS_READ:
      sys_read ((void*)(arg_+USER_BASE));
      break;
    case SYS_SBRK:{
      u32 addr = sys_sbrk (arg_);
      RETURN(addr,ptr);
      }break;
    default:
      kprintf ("undefined syscall...\n");
      RETURN(-1,ptr);
      break;
  }
  return;
}
