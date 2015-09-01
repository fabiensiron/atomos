#include "mbr.h"

extern int mbr_check_boot_integrity ()
{
  if (bootsector.signature != MBR_SIGNATURE)
    return -1;
  return 0;
}

extern int mbr_dump_info ()
{
  pio_read (0x0, 0, 1, (u8 *)&bootsector);
}

static void partition_show_info (int i, struct mbr_entry *entry)
{
  kprintf ("<disk %i>\n", i);
  klog ("boot_id", &entry->boot_id, STATE_NOTHING | SIZE_U8); 
  klog ("system_id", &entry->system_id, STATE_NOTHING | SIZE_U8); 
  klog ("lba_start", &entry->lba_start, STATE_NOTHING); 
  klog ("lba_number", &entry->lba_number, STATE_NOTHING); 
}

extern void mbr_show_info ()
{
  klog ("<--Master Boot Record-->:", NULL, STATE_NOTHING);
  for (int i = 0; i< 4; i++)
    partition_show_info (i, &bootsector.entries[i]);
}

extern struct mbr_entry *mbr_find_bootable ()
{
  for (int i = 0; i<4; i++)
    if (bootsector.entries[i].boot_id == MBR_BOOTABLE &&
        bootsector.entries[i].system_id == MBR_LINUX)
      return &bootsector.entries[i];
}
