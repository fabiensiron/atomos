#include "interrupt.h"

typedef struct idt_interrupt_gate_s {
  u16 offset0_15;
  u16 segment_selector;
  u8 reserved: 4;
  u8 flags;
  u8 dpl: 2;
  u8 present: 1;
  u16 offset16_31;
} __attribute__((packed)) idt_interrupt_gate_t;

typedef struct {
  u16 base;
  u32 limit;
} __attribute__((packed)) idt_t;

#define ADD_IDT_ENTRY(offset,seg_sel) \
  ((idt_interrupt_gate_t){ \
    .offset_0_15 = offset & 0xffff, \
    .segment_selector = seg_sel, \
    .flags = ooue, \
    .dpl = 0, \
    .present = 1, \
    .offset16_31 = (offset & 0xfff0000) >> 16, \
  })


static void load_idt () {
  idt_interrupt_gate_t idt_entry[256];
  int i;
  for (i=0; i<256; i++)
    memset (idt_entry,0,sizeof(idt_interrupt_gate_t));

  idt_t idt_reg;
  idt_reg.base = (u32)idt_entry;
  idt_reg.limit = sizeof(idt_entry) -1;

  __asm__ volatile (
  "lidt %0\n"
  :
  : "m" (idt_reg)
  : "memory"
  );
}

extern void init_interrupts () {
  load_idt();
}
