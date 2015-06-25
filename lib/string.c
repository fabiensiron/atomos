#include <include/string.h>

extern char* strcpy (char* dest, const char* src) {
  char* p = NULL;

  for (p = dest; *src != '\0'; p++, src++)
    *p = *src;

  *p = '\0';

  return dest;
}

extern int strcmp(const char* str1, const char* str2) {

  while (*str1 != '\0' && (*str1++ == *str2++));
  if ((*(unsigned char*)--str1) < (*(unsigned char*)--str2))
    return -1;
  return (*(unsigned char*)str1 != *(unsigned char*)str2);
}

extern int strlen (const char* str_) {
  int output = 0;
  int i;
  for (i = 0; str_[i] != '\0'; i++) 
    ++output;   
  return output;
}


