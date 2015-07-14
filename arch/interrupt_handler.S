/* Exceptions handle */

.extern error_isr
.extern panic 
.extern refresh_ps2_controller
.extern syscall

.macro SAVE_REG 
  pusha
  pushw %ds
  pushw %es
  pushw %fs
  pushw %gs
  pushl %ebx
  mov $0x10, %bx
  mov %bx, %ds
  popl %ebx
.endm

.macro RESTORE_REG 
  popw %gs
  popw %fs
  popw %es
  popw %ds
  popa
.endm


.globl no_error_wrapper
no_error_wrapper:
  pusha
  push $0
  call error_isr
  add $0x04, %esp
  popa
  iret

.globl error_wrapper
error_wrapper:
  pusha
  call error_isr
  popa
  iret

.globl critical_exception
critical_exception:
  push $0
  call panic

/* IRQ handle */


.globl keyboard_IRQ
keyboard_IRQ:
  SAVE_REG
  call refresh_ps2_controller
  movb $0x20, %al
  outb %al, $0x20
  RESTORE_REG
  iret

.globl syscall_handler
syscall_handler:
  SAVE_REG
  push %eax
  push %ebx
  call syscall 
  pop %ebx
  pop %eax
  RESTORE_REG
  iret
