#include <include/string.h>

extern char* reverse (const char* str_) {
  int len = strlen (str_);
  char output[len]; 

  for (int i = len -1; len >= 0; i--) {


  }
}

extern int strlen (const char* str_) {
  int output = 0;
  int i;
  for (i = 0; str_[i] != '\0'; i++) 
    ++output;   
}

