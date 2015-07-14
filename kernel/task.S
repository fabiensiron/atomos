/* TODO pass this in C and put the user stack dynamic */

.global load_task
load_task:
  cli
  push $0x23 // ss
  push $0x9000 // sp
  pushfl // flags
  popl %eax 
  orl $0x200, %eax // enable IF
  and $0xffffbfff, %eax // disable NT (no hardware commutation)
  push %eax
  push $0x1b // cs
  push $0x0 // ip
  movw $0x23, %ax // new ds
  movw %ax, %ds
  iret
