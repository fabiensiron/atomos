#define MAGIC 0x2BADB002
#define FLAGS 0x7

.section .multiboot
  .align 4
  .long MAGIC
  .long FLAGS
  .long -(MAGIC + FLAGS)

.text

.globl kernel_entry
kernel_entry:
  push %ebx /* multiboot_info_t* */
  push %eax /* magic */
  call kernel_main
  /* because I'm paranoid */
  loop:
    hlt
    jmp loop
