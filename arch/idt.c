#include "interrupt.h"
#include "exception.h"
#include "include/stdlib.h"
#include "drivers/vga_text.h"

#define SIZE_IDT 48

struct idt_interrupt_gate_s {
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

struct idt_s {
  u16 limit;
  u32 base;
} __attribute__((packed, aligned(8))) idt_t;

#define ADD_IDT_ENTRY(offset,seg_sel) \
  ((struct idt_interrupt_gate_s){ \
    .offset0_15 = offset & 0xffff, \
    .segment_selector = seg_sel, \
    .reserved = 0, \
    .flags = 0, \
    .type = 0x6, \
    .op_size = 1, \
    .zero = 0, \
    .dpl = 0, \
    .present = 1, \
    .offset16_31 = (offset >> 16) & 0xffff \
  })

#define NULL_ENTRY \
  ((struct idt_interrupt_gate_s){ \
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

static struct idt_interrupt_gate_s idt_entry[SIZE_IDT];

void double_fault_handler (void);
void zero_handler (void);


static void set_idt_handler (u8 index, u32 handler, u8 seg_sel) {
  struct idt_interrupt_gate_s* idt = idt_entry + index;
  if (handler == (u32)NULL) {
    idt->offset0_15 = 0;
    idt->offset16_31 = 0;
    idt->present = 0;
    idt->segment_selector = seg_sel;
  } else {
    idt->offset0_15 = handler & 0xffff;
    idt->segment_selector = seg_sel;
    idt->present = 1;
    idt->offset16_31 = (handler >> 16) & 0xffff;
  }
}

static void load_idt () {
    for (int i=0; i<SIZE_IDT; i++) 
    {
      struct idt_interrupt_gate_s* idt = idt_entry +i;
      idt->segment_selector = 0x8;
      idt->reserved = 0;
      idt->flags = 0;
      idt->type = 0x6;
      idt->op_size = 1;
      idt->zero = 0;
      set_idt_handler (i, (u32)NULL, 0);
    }

  struct idt_s idt_reg;
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
  // idt_entry [EXCEPTION_DIVIDE_ERROR] = ADD_IDT_ENTRY((u32)zero_handler, 0x8);
  pic_init ();

  set_idt_handler (EXCEPTION_DIVIDE_ERROR, (u32)zero_handler, 0x8);
  set_idt_handler (EXCEPTION_DOUBLE_FAULT, (u32)double_fault_handler, 0x8);
  STI;
}

extern void error_isr () {
  write_text_vga ("prout");  
}
