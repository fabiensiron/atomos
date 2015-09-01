#ifndef _EXT2_H_
#define _EXT2_H_

#include <include/kernel.h>
#include <include/mem.h>
#include <drivers/pio.h>
#include <include/log.h>

# define EXT2_MAGIC 0xef53

struct ext2_sb {
  u32 inodes_count;
  u32 blocks_count;
  u32 r_blocks_count;
  u32 free_blocks_count;
  u32 free_inodes_count;
  u32 first_data_block;
  u32 log_block_size;
  u32 log_frag_size;
  u32 blocks_per_group;
  u32 frags_per_group;
  u32 inodes_per_group;
  u32 mtime;
  u32 wtime;
  u16 mnt_count;
  u16 max_mnt_count;
  u16 magic; /* 0xef53 */
  u16 state;
  u16 errors;
  u16 minor_rev_level;
  u32 lastcheck;
  u32 checkinterval;
  u32 creator_os;
  u32 rev_level;
  u16 def_resuid;
  u16 def_resgid;
  u32 first_ino;
  u16 inode_size;
  u16 block_group_nr;
  u32 feature_compat;
  u32 feature_incompat;
  u32 feature_ro_compat;
  u8 uuid[16];
  char volume_name[16];
  char last_mounted[64];
  u32 algo_bitmap;
  u8 padding[820];
} __attribute__ ((packed));

struct disk {
  int device;
  struct ext2_super_block *sb;
  u32 blocksize;
  u16 groups;
  struct ext2_group_desc *gd;
};

struct ext2_gd {
  u32 block_bitmap;
  u32 inode_bitmap;
  u32 inode_table;
  u16 free_blocks_count;
  u16 free_inodes_count;
  u16 used_dirs_count;
  u16 pad;
  u32 reserved[3];
} __attribute__ ((packed));

struct ext2_inode {
  u16 mode;
  u16 uid;
  u32 size;
  u32 atime;
  u32 ctime;
  u32 mtime;
  u32 dtime;
  u16 gid;
  u16 links_count;
  u32 blocks;
  u32 flags;
  u32 osd1;
  u32 block[15];
  u32 generation;
  u32 file_acl;
  u32 dir_acl;
  u32 faddr;
  u8 osd2[12];
} __attribute__ ((packed));

struct directory_entry {
  u32 inode;
  u16 rec_len;
  u8 name_len;
  u8 file_type;
  char name;
} __attribute__((packed));

struct ext2_disk {
  int device;
  struct ext2_sb *sb;
  struct ext2_gd *gd;
  u32 blocksize;
  u16 groups;
};

struct ext2_disk disk;

extern int ext2_init (int,u32);
extern int ext2_check_integrity ();

extern struct ext2_sb *ext2_read_sb (int);
extern struct ext2_gd *ext2_read_gd ();
extern struct ext2_inode *ext2_read_inode (int);

#endif /* _EXT2_H_ */
