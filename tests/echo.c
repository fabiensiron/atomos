#include <stdlib.h>
#include <stdio.h>

const int a = 6;

void mem_test () {
  void* addr = malloc (0);
  printf ("%x\n" ,addr);
 // int* buf = malloc (sizeof(5));

}

int main () {

  printf ("\n############################\n");
  printf ("####### Hello World! #######\n");
  printf ("############################\n\n");
  while (1) {
    printf ("$ ");
    char buffer[80];
    read (buffer);
    if (buffer[0] == 't')
      test ();
    else if (buffer[0] == 'm')
      mem_test();
    else
      printf ("\n%s\n", buffer);
  }
  for (;;)
    ;
  return 0;
}
