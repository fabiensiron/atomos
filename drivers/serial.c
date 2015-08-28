#include "serial.h"

static u16 get_divisor () 
{
  return SERIAL_CLK_FREQ / BAUDRATE; 
}

# define LB(v) (v&0x0f)
# define HB(v) ((v>>8)&0xf)

extern void serial_init () 
{
  /* disable interrupts */
  OUTB(0x0,COM1+1); 
  /* enable dlab (baud rate divisor) */
  OUTB(0x80,COM1+3);
  /* set divisor */
  u16 div = get_divisor ();
  OUTB(LB(div),COM1+0); 
  OUTB(HB(div),COM1+1);
  /* 8 bits, no parity, one stop byte */
  OUTB(0x03,COM1+3); 
  /* fifo 14-byte threshold */
  OUTB(0xc7,COM1+2);
  /* irqs enabled */
  OUTB(0x0b,COM1+4);
}

static void wait_for_serial () 
{
  while ((INB(COM1+5) & 0x20) == 0)
    ;
}

extern void serial_putc (char c_) 
{
  wait_for_serial ();

  OUTB(c_,COM1);
}
