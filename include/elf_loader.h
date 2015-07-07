#ifndef _ELF_LOADER_H
#define _ELF_LOADER_H

#include <include/kernel.h>
#include <include/stdio.h>
#include <arch/multiboot.h>

#define PT_LOAD 1

void* brk;

typedef struct {
  unsigned char e_ident[16]; /* ID bytes */
  u16 e_type; /* file type */
  u16 e_machine; /* machine type */
  u32 e_version; /* version numb */
  u32 e_entry; /* entry point */
  u32 e_phoff; /* program hdr offset */
  u32 e_shoff; /* section hdr offset */ 
  u32 e_flags; /* flags proc */
  u16 e_ehsize; /* sizeof ehdr */
  u16 e_phentsize; /* program header entry size */
  u16 e_phnum; /* numb of program headers */
  u16 e_shentsize; /* section header entry size */
  u16 e_shnum;  /* numb of section headers */
  u16 e_shstrndx; /* string table index */
} Elf32_Ehdr;

typedef struct {
  u32 p_type;
  u32 p_offset;
  u32 p_vaddr;
  u32 p_paddr;
  u32 p_filesz;
  u32 p_memsz;
  u32 p_flags;
  u32 p_align;
} Elf32_Phdr;

extern void load_elf (u32 addr_);

#endif /* _ELF_LOADER_H */
