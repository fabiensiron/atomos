#include <include/syscall.h>
#include <arch/pm.h>

static void sys_write (char* arg) {
  kprintf ("%s", arg);
}

static void sys_read (u8* buffer) {
  wait_input (buffer);   
}

extern void syscall (u32 num_, u32 arg_) {
  switch (num_) {
    case SYS_WRITE:
      sys_write ((void*)(arg_+USER_BASE));  
      break;
    case SYS_READ:
      sys_read ((void*)(arg_+USER_BASE));
      break;
    default:
      kprintf ("num: %x, addr: %x", num_, arg_);
      kprintf ("Je crois qu'il y a eu un syscall...");
      break;
  }
}
