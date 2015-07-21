#include "syscall.h"

extern void* sbrk (unsigned int offset_) {
  SYSCALL (SYS_SBRK, offset_);
}

extern void write (char* str) {
  SYSCALL (SYS_WRITE, str);
}

extern void read (char* buffer) {
  SYSCALL (SYS_READ, buffer);
}

extern void test () {
  printf ("\n");
  int a = SYSCALL (4,2);
  printf (" test: %x\n", a);
}
