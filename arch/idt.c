#include "interrupt.h"
#include "exception.h"

#define SIZE_IDT 32

typedef struct idt_interrupt_gate_s {
  u16 offset0_15;
  u16 segment_selector;
  u8 reserved: 5;
  u8 flags: 3;
  u8 type: 3;
  u8 op_size: 1;
  u8 zero: 1;
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
    .offset0_15 = offset & 0xffff, \
    .segment_selector = seg_sel, \
    .reserved = 0, \
    .flags = 0, \
    .type = 0x6, \
    .op_size = 1, \
    .zero = 0, \
    .dpl = 0, \
    .present = 1, \
    .offset16_31 = (offset & 0xfff0000) >> 16 \
  })

#define NULL_ENTRY \
  ((idt_interrupt_gate_t){ \
    .offset0_15 = 0, \
    .segment_selector = 0x8, \
    .reserved = 0, \
    .flags = 0, \
    .type = 0x6, \
    .op_size = 1, \
    .zero = 0, \
    .dpl = 0, \
    .present = 0, \
    .offset16_31 = 0 \
   })

static idt_interrupt_gate_t idt_entry[SIZE_IDT];

static void load_idt () {
  int i;
  for (i=0; i<SIZE_IDT; i++) {
    idt_entry[i] = NULL_ENTRY; 
  }

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

void double_fault_handler (void);

extern void init_interrupts () {
  load_idt();
  idt_entry [EXCEPTION_DOUBLE_FAULT] = ADD_IDT_ENTRY((u32)double_fault_handler, 0x8);
  STI;
}
