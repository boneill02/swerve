# swerve

A suckless-inspired Unix-like kernel originally designed for i386 machines. This
is a work in progress. Please don't run this on real hardware. I take no
responsibility for damages caused by swerve (code is licensed with no warranty).


## Principles

1. The program should be free software.
1. The program should be as efficient as possible.
1. The program should be as legible as possible.
1. The program should be as small as possible.

## Prerequisites for building

* [GNU Binutils cross-compiled for
  swerve](https://gitlab.com/swegbun/swerve-binutils)
* [GCC cross-compiled for swerve](https://gitlab.com/swegbun/swerve-gcc)
* GNU Make
* A POSIX shell (`dash`, `bash`, ...)

## Prerequisites for making a GRUB image

* fdisk (from util-linux)
* GNU GRUB

## Building

1. Run `make -j3` (note: you should change 3 with the number of cores you have
   plus 1)

## Run in QEMU

1. Run `make run-qemu`

## Build GRUB image

1. Run `make grub-image`
