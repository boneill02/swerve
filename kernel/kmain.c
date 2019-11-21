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

#include "kmain.h"

#include "drivers/tty.h"
#include "drivers/serial/rs232.h"
#include "mm/wmalloc.h"

const char *version_info = "swerve v" VERSION "-" ARCH;

void kmain(void)
{
	int i;

	/* initialize drivers */
	rs232_initialize();

#ifdef DEBUG
	rs232_println("* Initialized RS-232 driver");
#endif

	terminal_initialize();
#ifdef DEBUG
	rs232_println("* Initialized VGA mode driver");
#endif

	/* print welcome */
	terminal_println(version_info);
	terminal_disable_cursor();
#ifdef DEBUG
	rs232_println("* Printed version info to VGA");
#endif

	/* initialize allocator */
	wminit(KERN_MEMORY_BASE, KERN_MEMORY_CEILING);
#ifdef DEBUG
	rs232_println("* Initialized watermark memory allocator");
#endif
}
