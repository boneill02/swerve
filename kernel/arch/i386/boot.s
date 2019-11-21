/*
 * This file is part of the swerve kernel.
 *
 * Copyright (C) 2019 Benjamin O'Neill <ben@benoneill.xyz>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
