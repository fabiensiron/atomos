#include "stdlib.h"

extern void* malloc (unsigned int len_) {

  return sbrk (len_);
}

extern void _start () {
  main();
  for (;;)
    ;
}
