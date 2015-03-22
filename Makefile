CC = gcc
CFLAGS = -m32 -Wall -nostdlib -nostdinc -std=c99
LDFLAGS = -nostdlib -m32 -Wl
TARGET = ATOMUX
OBJECT = arch/crt0.o kernel/main.o 

all: $(TARGET)
