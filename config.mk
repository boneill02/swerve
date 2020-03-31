VERSION = 0.01a-dev

# user configurable options
ARCH = i386
ARCH_PREFIX = $(ARCH)-swerve
LIBC_INCLUDE = "-I/usr/local/include/swerve"
LIBC_LIB_DIR = "-L/usr/local/lib/swerve"

DRIVERS = -DRS232_DRIVER

AS = $(ARCH_PREFIX)-as
CC = $(ARCH_PREFIX)-gcc
LD = $(CC)
AR = $(ARCH_PREFIX)-ar
RANLIB = $(ARCH_PREFIX)-ranlib
ASFLAGS = -W
CPPFLAGS = -DARCH="\"$(ARCH)\"" -DVERSION="\"$(VERSION)\"" $(DRIVERS)
CFLAGS = $(CPPFLAGS) -Wall -Os -ffreestanding -fno-pie -std=c99 -pedantic -nostdinc \
		-I$(SRC_DIR)/drivers $(LIBC_INCLUDE)
LDFLAGS = -nostdlib -static -ffreestanding -fno-stack-protector \
		 -fPIC -T$(ARCH_SRC_DIR)/linker.ld $(LIBC_LIB_DIR)
TARGET = swerve
