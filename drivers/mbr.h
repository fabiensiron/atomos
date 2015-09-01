#ifndef _MBR_H_
#define _MBR_H_

# include <include/kernel.h>
# include <drivers/pio.h>
# include <include/log.h>

# define MBR_SIGNATURE  0xaa55
# define MBR_BOOTABLE   0x80
# define MBR_LINUX      0x83

struct mbr_entry
{
  u8 boot_id;
  u8 begin_head;
  u8 begin_sect;
  u8 begin_cycl;
  u8 system_id;
  u8 end_head;
  u8 end_sect;
  u8 end_cycl;
  u32 lba_start;
  u32 lba_number;
} __attribute__((packed));

struct mbr_bootsector
{
  u8 stage1[446];
  struct mbr_entry entries[4];
  u16 signature;
} __attribute__((packed));

static struct mbr_bootsector bootsector;

extern int mbr_check_boot_integrity ();
extern int mbr_dump_info ();
extern void mbr_show_info ();
extern struct mbr_entry *mbr_find_bootable ();

# endif /* _MBR_H_ */
