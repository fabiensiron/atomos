print_usage (){
  echo "Usage: $0 ATOMUX"
  echo "...   then qemu ATOMUX_BOOTABLE"
}


################################

# print_usage
qemu-system-i386 -kernel ATOMOS
