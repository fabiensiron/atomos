#include <include/syscall.h>

extern void syscall (u32 num_, u32 arg_) {
  kprintf ("Je crois qu'il y a eu un syscall...");
}
