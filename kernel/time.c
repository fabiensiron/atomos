#include <include/time.h>


/* very useful before the init of the pit */
void pause ()
{
  for (int i = 0; i < PAUSE_DELAY; i++)
    ;
}

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


