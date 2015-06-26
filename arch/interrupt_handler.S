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
