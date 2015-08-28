# Atomos #

Atomos is a light-weight kernel based on several small kernels like
Linux 0.01, SimpleOS, Pepin, K (LSE). 
It's a monolithic and monotask kernel. 


### Why? ###


### How to run it? ###
dependencies: Qemu

```
#!shell

# with debug
./configure --debug --userland=test
# or without
./configure --userland=test
make
make boot
```


### Contributors ###


### Bug report ###
