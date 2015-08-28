#include <include/mem.h>

#if 0
static void actualize_seg (u32 new_brk_) {
   reset_segment (USER_DATA_SEGMENT, (u32)USER_BASE,
      (u32)(new_brk_+USER_BASE), 3,0);
}
#endif

extern void mem_init () {
  k_brk = (void*)0x200000;
}

extern u32 ksbrk (u32 offset_) {
  u32 base = (u32)k_brk;
  k_brk += offset_;

#if 0
  actualize_seg ((u32)brk);
#endif

  return base;
}

extern int kbrk (const void* addr_) {
  if (addr_ == NULL)
    return -1;

  u32 addr = ksbrk (0);
  u32 offset = (u32)addr_ - addr;
  ksbrk (offset);
  return 0;
}

/* this is just for test (on ksbrk) */
extern void* dummy_kmalloc (size_t size) {
  void *p = (void*)ksbrk (0);
  ksbrk (size);
  return p;
}

static struct s_heap_block* find_block (struct s_heap_block** last, size_t s) {
  struct s_heap_block* b = base;
  while (b && !(b->free && b->size >= s)) {
    *last = b;
    b = b->next;
  }
  return b;
}

static struct s_heap_block* extend_heap (struct s_heap_block* last, size_t s) {
  struct s_heap_block* b = (void*)ksbrk (0);
  (void*)ksbrk (BLOCK_SIZE+s);
  b->size = s;
  b->next = NULL;
  if (last) {
    last->next = b;
  } 
  b->free = 0;
}

static void split_block (struct s_heap_block* b, size_t s) {
  struct s_heap_block *new;
  new = b->data + s;
  new->size = b->size - s - BLOCK_SIZE;
  new->next = b->next;
  new->free = 1;
  b->size = s;
  b->next = new->next;
}

#define align4(x) (((((x)-1)>>2)<<2)+4)

extern void* kmalloc (size_t size) {
  struct s_heap_block *b,*last;
  size_t s = align4(size);
  if (base) {
    last = base;
    b = find_block (&last,s);
    if (b) {
      if ((b->size - s) >= BLOCK_SIZE+4) 
        split_block (b,s); 
      b->free = 0;
    } else {
      b = extend_heap (last, s);
    }
  } else {
    b = extend_heap (NULL, s);
    base = b;
  }
  return b->data;
}
