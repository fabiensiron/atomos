#include "8259.h"

extern void pic_init() {
  OUTB(0x11, _MASTER);
  OUTB(0x11, _SLAVE);
  
  OUTB(0x20, _MASTER+1);
  OUTB(0x28, _SLAVE+1);

  OUTB(0x4, _MASTER+1);
  OUTB(0x2, _SLAVE+1);

  OUTB(0x1, _MASTER+1);
  OUTB(0x1, _SLAVE+1);

  OUTB(0xFB, _MASTER+1);
  OUTB(0xFF, _SLAVE+1);
}
