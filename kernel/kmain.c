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

#include <stdio.h>
#include <string.h>

#include "kmain.h"

#include "drivers/terminal.h"
#include "drivers/tty.h"
#include "drivers/serial/rs232.h"

const char *version_info = "swerve v" VERSION "-" ARCH;

void kmain(void)
{
	/* initialize drivers */
	meminit();
	rs232_initialize();
	terminal_initialize();
	tty_init();

#ifdef DEBUG
	printf("* Initialized drivers\n");
#endif

	/* print welcome */
	printf(version_info);
}
