#include <include/stdlib.h>

extern void* memset (void* p, int c, size_t n) {
  int* i = NULL;
  for (i = p; n > 0; n--, i++)
    *i = c;

  return p;
}

extern int memcmp (const void* p1, const void* p2, size_t n) {
  const int* i1 = NULL;
  const int* i2 = NULL;

  for (i1 = p1, i2 = p2; (*i1 == *i2) && n>0; n--, i1++, i2++)
    continue;

  return n;
}

extern void* memcpy (void* p1, const void* p2, size_t n) {
  int* i1 = NULL;
  const int* i2 = NULL;

  for (i1 = p1, i2 = p2; n>0; n--, i1++, i2++)
    *(i1) = *(i2);

  return p1;
}
