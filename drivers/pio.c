#include <drivers/pio.h>

#define PIO_COMMON(drive,numblock,count) { \
      OUTB(0x00,0x1F1);    \
      OUTB(count,0x1F2);   \
      OUTB((u8)numblock,0x1F3);  \
      OUTB((u8)(numblock>>8),0x1F4); \
      OUTB((u8)(numblock>>16),0x1F5); \
      OUTB(0xE0 | (drive << 4) | ((numblock>>24)&0x0f),0x1F6); \
  }
  

#define PIO_WRITE 0x30
#define PIO_READ  0x20

extern int pio_read (int drive_, u32 lba_, int count_,
    u8* buf_) {
  u16 tmp;
  PIO_COMMON (drive_,lba_,count_);
  OUTB(PIO_READ,0x1F7);

  while (!(INB(0x1F7)&0x8));
  
  for (int idx = 0; idx < count_ * 256; idx++) {
    tmp = INW(0x1F0);
    buf_[idx*2] = (u8)tmp; 
    buf_[idx*2+1] = (u8)(tmp >> 8);
  }
  return count;
}
/*
extern int pio_write (int drive_, int numblock_, int count_,
    u8* buf_) {
  u16 tmp;
  PIO_COMMON (drive_,numblock_,count_);
  OUTB(PIO_WRITE,0x1F7);

  while (!(INB(0x1F7)&0x8));

  for (int idx = 0; idx < count_ * 256; idx++) {
    tmp = buf_[idx*2] | (buf_[idx*2+1]<< 8);
    OUTW(tmp,0x1F0);
  }
}

*/
