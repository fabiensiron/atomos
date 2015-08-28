#!/bin/bash

print_usage (){
  echo "Usage: $0 --floppy"
  echo "....or.$0 --qemu"
}


################################

if [ $# -eq 1 ] && [ $1 == "--floppy" ]; then
  cp tools/floppy atomos_floppy
  mcopy -i atomos_floppy ATOMOS ::/modules/k
  mcopy -i atomos_floppy tests/test ::/modules/rom
  qemu-system-i386 -fda atomos_floppy -serial stdio &
elif [ $# -eq 1 ] && [ $1 == "--qemu" ]; then
# print_usage
  qemu-system-i386 -kernel ATOMOS -serial stdio
else
  print_usage
fi
