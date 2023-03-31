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

/* entry point of our kernel */
ENTRY(_start)

SECTIONS
{
	/* we need 1MB of space at least */
	. = 1M;

	/* text section */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* read only data section */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* data section */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* bss section */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

}
