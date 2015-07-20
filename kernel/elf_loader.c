#include <include/elf_loader.h>


extern void load_elf (u32 addr_) {
  module_t* grub_mods = (void*)addr_;
  Elf32_Ehdr *hdr = (void*)grub_mods[0].mod_start;
  Elf32_Phdr *phdr = (void*)((char*)hdr + hdr->e_phoff);

  u32 highest = 0;

  for (int i = 0; i < hdr->e_phnum; i++) {
    if (phdr[i].p_type == PT_LOAD) {
      memcpy ((char*)(USER_BASE+phdr[i].p_paddr),
          (void*)((char*)hdr+phdr[i].p_offset), 
          phdr[i].p_filesz);


      memset((void*)USER_BASE+phdr[i].p_paddr + phdr[i].p_filesz,0,
          phdr[i].p_memsz - phdr[i].p_filesz);
      
      if (highest < phdr[i].p_paddr + phdr[i].p_memsz)
        highest = phdr[i].p_paddr + phdr[i].p_memsz; 

    }
  }

  u32 entry = (u32)(hdr->e_entry);

  brk = (void*)highest;
} 
