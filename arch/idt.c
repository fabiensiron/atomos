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

static struct idt_interrupt_gate_s idt_entry[SIZE_IDT];

void critical_exception (void);
void no_error_wrapper (void);
void error_wrapper (void);

static void set_idt_handler (u8 index, u32 handler, u8 seg_sel) {
  struct idt_interrupt_gate_s* idt = idt_entry + index;
  if (handler == (u32)NULL) {
    idt->offset0_15 = 0;
    idt->offset16_31 = 0;
    idt->present = 0;
    idt->dpl = 0; 
  } else {
    idt->offset0_15 = handler & 0xffff;
    idt->dpl = 0;
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
  pic_init ();
  load_idt();
  // idt_entry [EXCEPTION_DIVIDE_ERROR] = ADD_IDT_ENTRY((u32)zero_handler, 0x8);

  set_idt_handler (EXCEPTION_DIVIDE_ERROR, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_DEBUG, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_NMI, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_BREAKPOINT, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_OVERFLOW, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_BOUND_RANGE, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_INVALID_OPCODE, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_NOT_AVAILABLE, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_DOUBLE_FAULT, (u32)critical_exception, 0x8);
  set_idt_handler (EXCEPTION_COPROC_OVERRUN, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_INVALID_TSS, (u32)error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_NO_SEGMENT, (u32)error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_STACK_FAULT, (u32)error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_GENERAL_FAULT, (u32)error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_PAGE_FAULT, (u32)error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_RESERVED0, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_X87_FLOAT, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_ALIGNMENT_CHECK, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_MACHINE_CHECK, (u32)critical_exception, 0x8);
  set_idt_handler (EXCEPTION_SIMD_FLOAT, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_VIRTUALIZATION, (u32)no_error_wrapper, 0x8);
  /* RESERVED 21 to 29 */
  for (int i = 21; i< 30; i++)
    set_idt_handler (i, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_SECURITY, (u32)no_error_wrapper, 0x8);
  set_idt_handler (EXCEPTION_RESERVED3, (u32)no_error_wrapper, 0x8);
  STI;
}

extern void error_isr (u8 error) {
  write_text_vga ("prout");  
}
