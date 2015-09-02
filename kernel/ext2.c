#include <include/ext2.h>

static u32 sb_offset;

/* tmp define */
# define SB_SECTOR sb_offset

static u16 compute_groups (struct ext2_sb *sb) 
{
  int a = sb->blocks_count / sb->blocks_per_group +
   ((sb->blocks_count % sb->blocks_per_group)?1:0);
  int b = sb->inodes_count / sb->inodes_per_group +
   ((sb->inodes_count % sb->inodes_per_group)?1:0);

  return (a>b)?a:b;
}

extern int ext2_check_integrity ()
{
  if (disk.sb->magic != EXT2_MAGIC)
    return -1;
  return 0;
}

extern int ext2_init (int device_, u32 entry)
{
  sb_offset = entry + 2;
  disk.device = device_;

  disk.sb = ext2_read_sb (disk.device);

  disk.blocksize = 1024 << disk.sb->log_block_size;
  disk.groups = compute_groups (disk.sb);

  disk.gd = ext2_read_gd ();

    //ext2_dump_root ();
}

extern struct ext2_sb *ext2_read_sb (int device_)
{
  struct ext2_sb *sb = kmalloc (512);
  pio_read (device_, SB_SECTOR, 1, (u8*)sb);
  return sb;
}

extern struct ext2_gd *ext2_read_gd ()
{
//  int offset = (disk.blocksize == 1024)?2+SB_SECTOR: 1024+SB_SECTOR*512;
  //int len = disk.groups * sizeof (struct ext2_gd);
  struct ext2_gd *gd = kmalloc (512);
  int dev = 0;
  pio_read (dev, SB_SECTOR+2, 1,(u8*)gd);
  return gd;
}

extern struct ext2_inode *ext2_read_inode (int num_)
{
  int index, offset, gr_num;
  struct ext2_inode *inode;
  inode = (struct ext2_inode *) kmalloc (512);

  gr_num = (num_ -1) / disk.sb->inodes_per_group;
  index = (num_ -1) % disk.sb->inodes_per_group; 
  offset = disk.gd[gr_num].inode_table * disk.blocksize + index *disk.sb->inode_size;

  pio_read (disk.device, offset/512, 1, (char *)inode);
  return inode;
}

extern int ext2_dump_root ()
{
  root = ext2_read_inode (EXT2_ROOT);
}
