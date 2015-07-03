#include "irq.h"

static void enable_irq (int num_, u32 isr_) {
  set_idt_handler (num_+32, isr_, 0x8);
  enable_irq_line (num_);
}


extern void init_irq () {
  /* map keyboard */ 
  enable_irq (KEYBOARD, (u32)keyboard_IRQ);
}
