VERSION = 0.01a-dev

# user configurable options
ARCH = i386
ARCH_PREFIX = $(ARCH)-elf
LIBC_INCLUDE = "-I/usr/local/include/swerve"
LIBC_LIB = "-L/usr/local/lib/swerve"

DRIVERS = -DRS232_DRIVER

AS = $(ARCH_PREFIX)-as
CC = $(ARCH_PREFIX)-gcc
LD = $(CC)
AR = $(ARCH_PREFIX)-ar
RANLIB = $(ARCH_PREFIX)-ranlib
ASFLAGS = -W
CPPFLAGS = $(LIBC_INCLUDE) -DARCH="\"$(ARCH)\"" -DVERSION="\"$(VERSION)\"" $(DRIVERS)
CFLAGS = $(CPPFLAGS) -Wall -Os -ffreestanding -fno-pie -std=c99 -pedantic -nostdinc \
		-I$(SRC_DIR)/drivers
LDFLAGS = -nostdlib -static -ffreestanding -fno-stack-protector \
		 -fPIC -T$(ARCH_SRC_DIR)/linker.ld $(LIBC_LIB) -lc
TARGET = swerve
