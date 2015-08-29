#include <include/time.h>

static void sleep_init () 
{
  pit_reset_count ();
}

static void sleep_wait (u16 t_)
{
  while (pit_get_count() < t_)
    ;
}

void sleep (u16 t_) 
{
  sleep_init ();
  sleep_wait (t_);
}
