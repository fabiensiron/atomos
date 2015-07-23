#include <include/ext2.h>

struct ext2_super {
  u32 inode_count;
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
  u32 mnt_count;
  u32 max_mnt_count;
  u32 magic; /* 0xef53 */
  u32 state;
  u32 errors;
  u32 minor_rev_level;
  u32 lastcheck;
  u32 checkinterval;
  u32 creator_os;
  u32 rev_level;
  u32 def_resuid;
  u32 def_resgid;
  u32 first_inode;
  u32 inode_size;
  u32 block_group_nr;
  u32 feature_compat;
  u32 feature_incompat;
  u32 feature_ro_compat;
  u8 uuid[16];
  char volume_name[16];
  char last_mounted[64];
  u32 algo_bitmap;
  u8 padding[820];
} __attribute__ ((packed));

