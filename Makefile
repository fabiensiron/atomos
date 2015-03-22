CC = gcc
CFLAGS = -m32 -Wall -Wextra -nostdlib -nostdinc -std=c99 
LDFLAGS = -nostdlib -m32  
TARGET = ATOMOS
SRC = kernel/main.c
ASM = arch/crt0.S
OBJ = $(SRC:.c=.o) $(ASM:.S=.o)
LINK_SCRIPT = atomos.lds
PWD := $(shell pwd)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) -T $(LINK_SCRIPT)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -I $(PWD) -c $<

%.o: %.S
	$(CC) -o $@ $(CFLAGS) -I $(PWD) -c $<

boot:
	./qemu_boot.sh

.PHONY: clean
clean:
	rm -rf arch/*.o
	rm -rf kernel/*.o

.PHONY: mrproper 
mrproper: clean
	rm -rf $(TARGET)
