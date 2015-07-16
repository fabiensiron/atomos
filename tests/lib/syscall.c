#include "syscall.h"

extern void write (char* str) {
  SYSCALL (SYS_WRITE, str);
}
