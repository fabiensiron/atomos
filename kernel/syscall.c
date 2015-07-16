#include <include/syscall.h>

static void sys_write (char* arg) {
  kprintf ("%s", arg);
}

extern void syscall (u32 num_, u32 arg_) {
  switch (num_) {
    case SYS_WRITE:
      sys_write ((char*)arg_);  
      break;
    default:
      kprintf ("num: %x, addr: %x", num_, arg_);
      kprintf ("Je crois qu'il y a eu un syscall...");
      break;
  }
}
