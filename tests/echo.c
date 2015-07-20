#include <stdlib.h>
#include <stdio.h>

const int a = 6;

int main () {

  printf ("\n############################\n");
  printf ("####### Hello World! #######\n");
  printf ("############################\n\n");
  while (1) {
    printf ("$ ");
    char buffer[80];
    read (buffer);
    printf ("\n%s\n", buffer);
  }
  for (;;)
    ;
  return 0;
}
