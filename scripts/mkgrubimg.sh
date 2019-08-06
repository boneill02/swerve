#!/bin/sh

dd if=/dev/zero of=$IMAGE.img bs=512 count=131072

cat << EOF | fdisk $IMAGE.img
n
p
1


t
b
a
w
EOF

losetup /dev/loop0 $IMAGE.img
losetup /dev/loop1 $IMAGE.img -o 1048576

mkdosfs -F32 -f 2 /dev/loop1
mount /dev/loop1 /mnt
grub-install --target=i386-pc --root-directory=/mnt --no-floppy --modules="normal part_msdos multiboot" /dev/loop0
cp $IMAGE /mnt/boot
cat > /mnt/boot/grub/grub.cfg << EOF
set timeout=15
set default=0
 
menuentry "swerve" {
	multiboot /boot/$IMAGE
	boot
}
EOF
umount /mnt
losetup -d /dev/loop0
losetup -d /dev/loop1
