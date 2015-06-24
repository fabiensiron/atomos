.extern error_isr

.globl zero_handler
zero_handler:
  prout:
    jmp prout

  pusha
  
  call error_isr

  popa

  iret

.globl double_fault_handler
double_fault_handler:
  1: 
    hlt
    jmp 1b

