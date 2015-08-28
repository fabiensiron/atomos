# Atomos #

Atomos is a light-weight kernel based on several small kernels like
Linux 0.01, SimpleOS, Pepin, K (LSE). 
It's a monolithic and monotask kernel. 


### Why? ###


### How to run it? ###
configure the kernel

```
#!shell

./configure --debug=2 --userland=test
# == DEBUG ==
#   0: no debug
#   1: debug in DEBUG file
#   2: vga debug
# == USER ==
#   none: no userland
#   test: test userland (simple cat without parameters)

```

dependencies: Qemu

```
#!shell

make
make boot
```


### Contributors ###


### Bug report ###
