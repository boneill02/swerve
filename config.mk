VERSION = 0.01a-dev

# user configurable options
ARCH = i386
ARCH_PREFIX = $(ARCH)-swerve
DEBUG = 1

AS=$(ARCH_PREFIX)-as
CC=$(ARCH_PREFIX)-gcc
LD=$(CC)
AR=$(ARCH_PREFIX)-ar
RANLIB=$(ARCH_PREFIX)-ranlib
ASFLAGS=-W
CPPFLAGS = -DARCH="\"$(ARCH)\"" -DVERSION="\"$(VERSION)\"" -DDEBUG -D__is_libk
CFLAGS= $(CPPFLAGS) -Wall -O3 -ffreestanding -fno-pie -std=c99 -pedantic -nostdinc \
		-I$(SRC_DIR)/drivers -I$(LIBC_DIR)/include
LDFLAGS=-static -nostdlib -ffreestanding -fno-stack-protector -fPIC -T$(ARCH_SRC_DIR)/linker.ld
TARGET=swerve
