#include "i8259.h"

extern void pic_init() {
  /* ICW1 with ICW4, cascaded and front (edge) */ 
  OUTB(0x11, _MASTER);
  OUTB(0x11, _SLAVE);
  
  /* ICW2 master_offset idt -> 32 slave_offset idt -> 40 */
  OUTB(0x20, _MASTER+1);
  OUTB(0x28, _SLAVE+1);

  /* ICW3 master/slave connection */
  OUTB(0x4, _MASTER+1);
  OUTB(0x2, _SLAVE+1);

  /* ICW4 default mode */
  OUTB(0x1, _MASTER+1);
  OUTB(0x1, _SLAVE+1);

  /* OCW1 masking */
  OUTB(0xFB, _MASTER+1);
  OUTB(0xFF, _SLAVE+1);
}

extern void enable_irq_line (int num_) {
  if (num_ < 8)
    OUTB (INB(_MASTER+1) & ~(1 << num_), _MASTER+1);
  else
    OUTB (INB(_SLAVE+1) & ~(1 << (num_-8)), _SLAVE+1);
}
