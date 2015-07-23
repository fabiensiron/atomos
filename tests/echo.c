#include <stdlib.h>
#include <stdio.h>

const int a = 6;

void mem_test () {
  int* a = malloc (sizeof (5));
  printf ("\n%x\n", a);
  a = malloc (sizeof (5));
  printf ("\n%x\n", a);
  a = malloc (sizeof (5));
  printf ("\n%x\n", a);
//  void* addr = malloc (0);
  //printf ("\n%x\n" ,addr);
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
    else if (buffer[0] == 'r'){
      int ret = read(buffer);
      printf ("\n%i\n", ret);
    } else
      printf ("\n%s\n", buffer);
  }
  for (;;)
    ;
  return 0;
}
