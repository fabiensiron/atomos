print_usage (){
  echo "Usage: $0 ATOMUX"
  echo "...   then qemu ATOMUX_BOOTABLE"
}


################################

if [ $# -eq 1 ] && [ $1 == "--bochs" ]; then
  dd if=/dev/zero of=floppy.img bs=1024 count=1440
  losetup /dev/loop1 floppy.img





elif [ $# -eq 1 ] && [ $1 == "--qemu" ]; then
# print_usage
  qemu-system-i386 -kernel ATOMOS
fi
