#include <include/elf_loader.h>

extern void load_elf (u32 addr_) {
  module_t* grub_mods = (void*)addr_;
  Elf32_Ehdr *hdr = (void*)grub_mods[0].mod_start;
  Elf32_Phdr *phdr = (void*)((char*)hdr + hdr->e_phoff);
  kprintf ("test mod: %s", hdr->e_ident);

  u32 highest = 0;

  for (int i = 0; i < hdr->e_phnum; i++) {
    if (phdr[i].p_type == PT_LOAD) {
      memcpy ((void*)phdr[i].p_paddr,hdr+phdr[i].p_offset, 
          phdr[i].p_filesz);

      memset((void*)phdr[i].p_paddr + phdr[i].p_filesz,0,
          phdr[i].p_paddr - phdr[i].p_memsz);
      
      if (highest < phdr[i].p_paddr + phdr[i].p_memsz)
        highest = phdr[i].p_paddr + phdr[i].p_memsz; 

    }
  }

  brk = (void*)highest;
  kprintf ("\nbrk: %x", brk);
} 
