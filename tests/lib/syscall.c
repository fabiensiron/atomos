#include "syscall.h"

extern void write (char* str) {
  SYSCALL (SYS_WRITE, str);
}

extern void read (char* buffer) {
  SYSCALL (SYS_READ, buffer);
}
