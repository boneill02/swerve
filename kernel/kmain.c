/*
 * This file is part of the swerve kernel.
 *
 * Copyright (C) 2019 the swerve development team (see AUTHORS.md).
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
#include <stdlib.h>
#include <string.h>

#include "kmain.h"

#include "drivers/terminal.h"
#include "drivers/tty.h"
#include "drivers/rs232.h"

const char *version_info = "swerve v" VERSION "-" ARCH;

void kmain(void)
{
	/* initialize hardware drivers */
	mem_init();
	terminal_init();
#ifdef RS232_DRIVER
	rs232_init();
#endif

	/* initialize software drivers */
	tty_init();

#ifdef DEBUG
	printf("* Initialized drivers\n");
#endif

	/* print welcome */
	const char *welcome = "welcome to swerve!";
	printf("%s\n", welcome);
#ifdef RS232_DRIVER
	setty(2);
	printf("%s\n", welcome);
#endif
}
