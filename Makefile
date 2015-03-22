CC = gcc
CFLAGS = -m32 -Wall -nostdlib -nostdinc -std=c99 -ffreestanding 
LDFLAGS = -nostdlib -m32 -L include 
TARGET = ATOMOS
SRC = kernel/main.c
ASM = arch/crt0.S
OBJ = $(SRC:.c=.o) $(ASM:.S=.o)
LINK_SCRIPT = atomos.lds
PWD := $(shell pwd)

all: $(TARGET)

$(TARGET): $(OBJ) $(LINK_SCRIPT)
	$(CC) -o $@ $^ $(LDFLAGS) -T $(LINK_SCRIPT)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -I $(PWD) -c $<

%.o: %.S
	$(CC) -o $@ $(CFLAGS) -I $(PWD) -c $<

.PHONY: clean
clean:
	rm -rf arch/*.o
	rm -rf kernel/*.o

.PHONY: mrproper 
mrproper:
	rm -rf $(TARGET)
