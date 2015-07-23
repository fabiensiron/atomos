/* TODO pass this in C and put the user stack dynamic */

.global load_task
load_task:
  cli
  pop %ebx
  pop %ebx
  push $0x23 // ss
  push $0x30000 // sp
  pushfl // flags
  popl %eax 
  orl $0x200, %eax // enable IF
  and $0xffffbfff, %eax // disable NT (no hardware commutation)
  push %eax
  push $0x1b // cs
  push %ebx // ip
  movw $0x23, %ax // new ds
  movw %ax, %ds
  iret
