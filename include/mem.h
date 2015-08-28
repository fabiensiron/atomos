#ifndef _MEM_H_
#define _MEM_H_

#include <include/kernel.h>
#include <include/syscall.h>
#include <arch/pm.h>

struct s_heap_block {
  size_t                size;
  struct s_heap_block*  next;
  int                   free;
  char               data[1];
};

#define BLOCK_SIZE         12

static void* base = NULL;

extern void mem_init ();
extern u32 ksbrk (u32 offset);
extern int kbrk (const void* addr);
extern void* kmalloc (size_t size);

#endif /* _MEM_M_ */
