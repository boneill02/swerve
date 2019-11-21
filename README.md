# swerve

A suckless-inspired Unix-like kernel originally designed for i386 machines.

## Principles

1. The program should be free software.
2. The program should be as efficient as possible.
3. The program should be as legible as possible.
4. The program should be as small as possible.

## Prerequisites for building

* GNU Binutils 2.32+
* GCC 9.1+ (only C support is necessary)
* GNU Make
* A POSIX shell (`dash`, `bash`...)

## Prerequisites for making a GRUB image

* fdisk (from util-linux)
* GNU GRUB

## Building

1. Build and install the toolchain to your $PATH:
   `./toolchain/build-toolchain.sh -j3` (note: replace the 3 with the number of
   cores you have plus 1)
2. Run `make -j3` (note: same thing as above, you should change 3 with the
   number of cores you have plus 1)

## Run in QEMU

1. Run `make run-qemu`

## Build GRUB image

1. Run `make grub-image`
