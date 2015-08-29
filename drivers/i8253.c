#include "i8253.h" 

# define LB(v) (v&0x0f)
# define HB(v) ((v>>8)&0xf)

void pit_init () 
{
  u16 count = PIT_ORIG_FREQ / PIT_FREQ;
  OUTB (0x34, PIT_CMD);
  OUTB (LB(count), PIT_CH0);
  OUTB (HB(count), PIT_CH0);
}

void pit_handler () 
{
  count++;
}

void pit_reset_count () 
{
  count = 0;
}

u32 pit_get_count ()
{
  return count;
}



