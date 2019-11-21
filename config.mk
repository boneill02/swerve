VERSION = 0.01a-dev

# user configurable options
ARCH = i386
ARCH_PREFIX = $(ARCH)-elf
DEBUG = 1

AS=$(ARCH_PREFIX)-as
CC=$(ARCH_PREFIX)-gcc
LD=$(CC)
ASFLAGS=-Wall
CPPFLAGS = -DARCH="\"$(ARCH)\"" -DVERSION="\"$(VERSION)\"" -DDEBUG
CFLAGS= $(CPPFLAGS) -Wall -O3 -ffreestanding -fno-pie -std=c99 -pedantic \
		-I$(SRC_DIR)/drivers -I$(LIBC_DIR)/include -nostdinc
LDFLAGS=-ffreestanding -fno-stack-protector -fPIC -nostdlib -T$(ARCH_SRC_DIR)/linker.ld
TARGET=swerve
