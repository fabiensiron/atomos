#!/bin/sh

usage()
{
  echo "Usage: $0"  
}


for i
do 
  case $i in
    "--help")
      usage
      exit 0
      ;;
  esac
done

ROOTDIR=../root
IMG_FILE=atomos.img
SECTOR_BEFORE_EXT2=63
SYSTEM_ID=83
EXT2_PARTITION_SIZE=32000
FAT32_PARTITION_SIZE=32000
EXT2_BLOCK_SIZE=1024
DISK_BLOCK_SIZE=512


create()
{
  rm -rf tools/mnt
  
  if [ -f $IMG_FILE ]; then
    rm $IMG_FILE
  fi

  TMP_FILE1=`mktemp XXXXXX`
  dd if=/dev/zero of=$TMP_FILE1 count=$SECTOR_BEFORE_EXT2 bs=$DISK_BLOCK_SIZE
  TMP_FILE2=`mktemp XXXXXX`
  dd if=/dev/zero of=$TMP_FILE2 count=$EXT2_PARTITION_SIZE bs=$EXT2_BLOCK_SIZE
  TMP_FILE3=`mktemp XXXXXX`
  dd if=/dev/zero of=$TMP_FILE3 count=$FAT32_PARTITION_SIZE bs=1024

  mkfs.ext2 -F -b $EXT2_BLOCK_SIZE $TMP_FILE2 || exit 1
  mkfs -t msdos $TMP_FILE3 || exit 1

  cat $TMP_FILE1 $TMP_FILE2 $TMP_FILE3 > $IMG_FILE
  rm -f $TMP_FILE1 $TMP_FILE2 $TMP_FILE3

  EXT2_PART_SIZE=$(( (EXT2_BLOCK_SIZE * EXT2_PARTITION_SIZE) / DISK_BLOCK_SIZE ))
  FAT_BEGIN=$(( SECTOR_BEFORE_EXT2 + EXT2_PART_SIZE ))

  sfdisk -qf $IMG_FILE > /dev/null 2>&1 <<- EOF
    # partition table of $IMG_FILE
        unit: sectors

    $(IMG_FILE)1 : start= $SECTOR_BEFORE_EXT2, size= $EXT2_PART_SIZE, Id= $SYSTEM_ID, bootable
    $(IMG_FILE)2 : start= $FAT_BEGIN, size= $FAT32_PARTITION_SIZE, Id= b
    $(IMG_FILE)3 : start= 0, size= 0, Id= 0
    $(IMG_FILE)4 : start= 0, size= 0, Id= 0
EOF
}

#create
LOOP=`sudo kpartx -afv $IMG_FILE | head -n 1 | cut -d " " -f 3`
sleep 1
echo $LOOP
sudo mkdir -p mnt/
sudo mount /dev/mapper/$LOOP mnt/ 
sudo cp -R $ROOTDIR/* mnt
sudo umount mnt
sudo rm -rf mnt
sudo kpartx -d $IMG_FILE



