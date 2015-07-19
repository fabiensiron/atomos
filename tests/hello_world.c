#include <stdlib.h>
#include <stdio.h>

const int a = 6;

int main () {
 char *str = "Hello World!\n";
 char str2[] = {'h', '\0'};
// write (str2);

  printf ("Hello World! \n");
  printf ("$ ");
  char buffer[80];
  read (buffer);
  printf ("\n%s", buffer);
  
  for (;;)
    ;
  return 0;
}
