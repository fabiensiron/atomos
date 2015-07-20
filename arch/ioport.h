#ifndef _IOPORT_H
#define _IOPORT_H

#define INB(port) ({ \
    unsigned char _v; \
    __asm__ volatile ( \
      "inb %w1, %0\n" \
      : "=a" (_v)  \
      : "Nd" (port)  \
      :   \
    );     \
    _v;   \
  })

#define INW(port) ({ \
    u16 _v; \
    __asm__ volatile ( \
      "inw %w1, %0\n" \
      : "=a" (_v) \
      : "Nd" (port) \
      : \
    );  \
    _v; \
    })

#define OUTB(data, port)  \
    __asm__ volatile ( \
      "outb %b0, %w1\n" \
      :   \
      :  "a" (data),\
        "Nd" (port)\
      :   \
    )    

#define OUTW(data, port)  \
    __asm__ volatile ( \
      "outw %w0, %w1\n" \
      :   \
      :  "a" (data),\
        "Nd" (port)\
      :   \
    )    

#define CLI \
  __asm__ volatile (\
      "cli\n" \
      : \
      : \
      : \
    ) 

#define STI \
    __asm__ volatile (\
      "sti\n" \
      : \
      : \
      : \
    ) 



#endif /* _IOPORT_H */
