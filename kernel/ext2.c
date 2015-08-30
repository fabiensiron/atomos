#include <include/ext2.h>

# define SB_OFFSET 2048
# define SB_SECTOR (SB_OFFSET/512)

static u16 compute_groups (struct ext2_sb *sb) 
{
  int a = sb->blocks_count / sb->blocks_per_group +
   ((sb->blocks_count % sb->blocks_per_group)?1:0);
  int b = sb->inodes_count / sb->inodes_per_group +
   ((sb->inodes_count % sb->inodes_per_group)?1:0);

  return (a>b)?a:b;
}

extern int ext2_init (int device_)
{
  disk.device = device_;
  disk.sb = ext2_read_sb (disk.device);
  disk.blocksize = 1024 << disk.sb->log_block_size;


  disk.groups = compute_groups (disk.sb);
  disk.gd = ext2_read_gd ();
}

extern struct ext2_sb *ext2_read_sb (int device_)
{
  struct ext2_sb *sb = kmalloc (sizeof(struct ext2_sb));
  pio_read (device_, SB_SECTOR, 2, (u8*)sb);
  return sb;
}

extern struct ext2_gd *ext2_read_gd ()
{
  //int offset = (disk.blocksize == 1024)?4: disk.blocksize/512;
  //int len = disk.groups * sizeof (struct ext2_gd);
  disk.gd = kmalloc (512);
  pio_read (disk.device, 2+SB_SECTOR, 1,(char *)disk.gd);
}

extern struct ext2_inode *ext2_read_inode (int num_)
{


}

