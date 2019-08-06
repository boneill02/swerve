# multiboot magic number
.set MAGIC,    0x1BADB002

# no flags
.set FLAGS,    0

# set the checksum
.set CHECKSUM, -(MAGIC + FLAGS)

# start multiboot section
.section .multiboot

# these should be longs
.long MAGIC
.long FLAGS
.long CHECKSUM

# end multiboot section, start 2kB stack now
stack_bottom:
.skip 4096
stack_top:

# end stack section, start text section

.section .text
.global _start
.type _start, @function

_start:

	# assign stack pointer
  	mov $stack_top, %esp

	# start the actual kernel
  	call kmain

	cli

# end loop
hlt_loop:

	hlt
	jmp hlt_loop

.size _start, . - _start
