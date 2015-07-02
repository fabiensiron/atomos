#include "exception.h"

/*static void divide_error (void);
static void debug (void);
static void nmi (void);
static void breakpoint (void);
static void overflow (void);
static void bourds (void);
static void invalid_opcode (void);
static void not_available (void);
static void double_fault (void);
static void coprocessor_overrun (void);
static void invalid_tss (void);
static void no_segment (void);
static void stack_fault (void);
static void general_fault (void);
static void page_fault (void);
static void coprocessor_error (void);
static void reserved (void); */

extern void exception_init () {
  for (int i = 0; i < SIZE_IDT; i++)
    set_idt_handler (i, (u32)critical_exception, 0x8);
}
