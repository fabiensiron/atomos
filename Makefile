SCRIPT_ARG=floppy
CC = gcc
CFLAGS = -m32 -g -Wall -Wextra -nostdlib -nostdinc -ggdb3 -std=c99 
LDFLAGS = -nostdlib -m32  
TARGET = ATOMOS
USER_TEST_DIR = tests
USER_TEST_TARGET = tests/test
SRC = arch/pm.c \
			arch/idt.c \
			arch/exception.c \
			arch/irq.c \
			kernel/main.c \
			kernel/panic.c \
			kernel/elf_loader.c \
			kernel/log.c \
			kernel/mem.c \
                        kernel/time.c \
			kernel/syscall.c \
			drivers/vga_text.c \
			drivers/i8259.c \
			drivers/i8042.c \
                        drivers/i8253.c \
			drivers/pio.c \
                        drivers/serial.c \
			lib/string.c \
			lib/stdlib.c \
			lib/stdio.c
ASM = arch/crt0.S kernel/task.S arch/interrupt_handler.S
OBJ = $(SRC:.c=.o) $(ASM:.S=.o)
LINK_SCRIPT = arch/atomos.lds
PWD := $(shell pwd)
CD := cd

all: test $(TARGET)

test:
	cd $(USER_TEST_DIR) && $(MAKE)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) -T $(LINK_SCRIPT)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -I $(PWD) -c $<

%.o: %.S
	$(CC) -o $@ $(CFLAGS) -I $(PWD) -c $<

boot:
	$(shell cp tools/floppy atomos_floppy)
	$(shell mcopy -i atomos_floppy ATOMOS ::/modules/k)
	$(shell mcopy -i atomos_floppy tests/test ::/modules/rom)
	qemu-system-i386 -fda atomos_floppy -serial stdio > DEBUG

.PHONY: clean
clean:
	rm -rf arch/*.o
	rm -rf kernel/*.o
	rm -rf drivers/*.o
	rm -rf lib/*.o
	rm -rf tests/*.o

.PHONY: mrproper 
mrproper: clean
	echo "" > DEBUG
	rm -rf atomos_floppy
	rm -rf $(TARGET)
