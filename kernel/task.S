/* TODO pass this in C and put the user stack dynamic */

//#define STACK_USER $0x30000
#define STACK_USER $0x30000

.global load_task
load_task:
  cli
  pop %ebx
  pop %ebx
  push $0x23 // ss
  push STACK_USER // sp
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
