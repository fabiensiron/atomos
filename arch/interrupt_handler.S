/* Exceptions handle */

.extern error_isr
.extern panic 


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

.extern refresh_ps2_controller

ack_int_A:
  movb $0x20, %al
  outb %al, $0x20

ack_int_B:
  movb $0x20, %al
  outb %al, $0x20
  outb %al, $0xA0

.globl keyboard_IRQ
keyboard_IRQ:
  pusha
  call refresh_ps2_controller
  call ack_int_A
  iret
