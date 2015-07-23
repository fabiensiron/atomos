#include "syscall.h"

extern void* sbrk (unsigned int offset_) {
  return SYSCALL (SYS_SBRK, offset_);
}

extern void write (char* str) {
  SYSCALL (SYS_WRITE, str);
}

extern unsigned int read (char* buffer) {
  return SYSCALL (SYS_READ, buffer);
}

extern void test () {
  printf ("\n");
  int a = SYSCALL (4,2);
  printf (" test: %x\n", a);
}
