#ifndef _STDLIB_H
#define _STDLIB_H

#include <syscall.h> 

inline 
  void _start () {
    main ();
    for (;;)
      ;
  }

#endif /* _STDLIB_H */
