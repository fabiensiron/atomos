CC = gcc
CFLAGS = -m32 -g -Wall -Wextra -nostdlib -nostdinc -fno-stack-protector -fno-builtin -ggdb3 -std=c99
LDFLAGS = -nostdlib -Wl,--build-id=none -m32  
TARGET = test
SRC = hello_world.c lib/syscall.c 
OBJ = $(SRC:.c=.o) 
PWD := $(shell pwd)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) -L /lib/stdlib.h -T lib/test.lds 

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -I $(PWD)/lib -c $<


.PHONY: clean
clean:
	rm *.o

.PHONY: mrproper 
mrproper: clean
	rm -rf $(TARGET)
