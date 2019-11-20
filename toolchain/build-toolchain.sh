#!/bin/sh

# getopt

# -- variables --
[ -z "$TARGET" ] && TARGET=i386-elf
[ -z "$GCC_VERSION" ] && GCC_VERSION=9.1.0
[ -z "$BINUTILS_VERSION" ] && BINUTILS_VERSION=2.32
[ -z "$MAKEFLAGS" ] && MAKEFLAGS="-j3"

# -- functions --
build_binutils() { \
	echo "Downloading binutils tarball"
	curl -O https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz >/dev/null 2>/dev/null
	echo "Extracting binutils tarball"
	gunzip binutils-$BINUTILS_VERSION.tar.gz
	tar -xf binutils-$BINUTILS_VERSION.tar
	rm binutils-$BINUTILS_VERSION.tar

	echo "Building binutils for $TARGET"
	mkdir build-binutils-$BINUTILS_VERSION
	cd build-binutils-$BINUTILS_VERSION
	../binutils-$BINUTILS_VERSION/configure --target=$TARGET --disable-werror
	MAKEFLAGS=$MAKEFLAGS make && sudo make install
}

build_gcc() { \
	echo "Downloading gcc tarball"
	curl -O https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz >/dev/null 2>/dev/null
	echo "Extracting gcc tarball"
	gunzip gcc-$GCC_VERSION.tar.gz
	tar -xf gcc-$GCC_VERSION.tar
	rm gcc-$GCC_VERSION.tar

	echo "Building gcc for $TARGET"
	mkdir build-gcc-$GCC_VERSION
	cd build-gcc-$GCC_VERSION
	../gcc-$GCC_VERSION/configure --target=$TARGET --enable-languages=c
	MAKEFLAGS=$MAKEFLAGS make all-gcc && sudo make install-gcc
}

# -- "actual script" --
echo "You must enter your password so this can (hopefully) install without any more user input"
sudo ls >/dev/null

[ -z "$(which $ARCH-as)" ]  && BINUTILS="y"
[ -z "$(which $ARCH-gcc)" ] && GCC="y"

[ -z $BINUTILS ] || build_binutils && echo "GNU Binutils is already installed for $TARGET"
[ -z $GCC ] || build_gcc && echo "GCC is already installed for $TARGET"
