#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

void sleep_test () {
  sleep (5000);
  printf ("\n");
}

int main () {

  unsigned long sp;
  __asm__ volatile (
    "mov %%esp,%0\n"
    :"=m"(sp)
    :
  );
  //printf ("%x\n",sp);

  printf ("\n############################\n");
  printf ("####### Hello World! #######\n");
  printf ("############################\n\n");
  while (1) {
    printf ("$ ");
    char buffer[80];
    read (buffer);
    if (buffer[0] == 't')
      sleep_test ();
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
