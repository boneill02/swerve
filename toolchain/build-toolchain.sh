#!/bin/sh

TARGET=i386-elf
GCC_VERSION=9.1.0
BINUTILS_VERSION=2.32
[ -z "$MAKEFLAGS" ] && MAKEFLAGS="$1"

curl -O https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz
curl -O https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz

gunzip binutils-$BINUTILS_VERSION.tar.gz
gunzip gcc-$GCC_VERSION.tar.gz

tar -xf binutils-$BINUTILS_VERSION.tar
tar -xf gcc-$GCC_VERSION.tar

mkdir build-binutils-$BINUTILS_VERISON
cd build-binutils-$BINUTILS_VERSION
../binutils-$BINUTILS_VERSION/configure --target=$TARGET --disable-werror
make
sudo make install

cd ..
mkdir build-gcc-$GCC_VERSION
cd build-gcc-$GCC_VERSION
../gcc-$GCC_VERSION/configure --target=$TARGET --enable-languages=c
make all-gcc
sudo make install-gcc
cd ..
