CC = gcc
CFLAGS = -m32 -Wall -Wextra -nostdlib -nostdinc -std=c99 -fno-stack-protector -fno-builtin 
LDFLAGS = -nostdlib -m32  
TARGET = ATOMOS
SRC = arch/pm.c \
			arch/idt.c \
			kernel/main.c \
			kernel/panic.c \
			drivers/vga_text.c \
			drivers/i8259.c \
			lib/string.c \
			lib/stdlib.c 
ASM = arch/crt0.S arch/interrupt_handler.S
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
	rm -rf drivers/*.o
	rm -rf lib/*.o

.PHONY: mrproper 
mrproper: clean
	rm -rf $(TARGET)
