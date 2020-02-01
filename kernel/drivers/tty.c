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

#include "tty.h"

#include "terminal.h"

#ifdef RS232_DRIVER
#include "rs232.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Initialize all TTY devices, including special ones. */
void tty_init(void)
{
	for (int i = 0; i < MAX_TTYS; i++) {
		ttys[i] = malloc(sizeof(TTY_Device));
		ttys[i]->controller.cursor_x = 0;
		ttys[i]->controller.cursor_y = 0;
		ttys[i]->controller.cursor_status = 1;
		ttys[i]->controller.buffer = malloc(8192);
		ttys[i]->controller.unwritten = 0;
		ttys[i]->controller.dev = NULL;
		((Device *)ttys[i])->read = tty_read;
		((Device *)ttys[i])->write = tty_write;
	}

	/* Special TTYs */
	ttys[0]->controller.dev = malloc(sizeof(Device));
	ttys[0]->controller.dev->write = terminal_write;
#ifdef RS232_DRIVER
	ttys[1]->controller.dev = malloc(sizeof(Device));
	ttys[1]->controller.dev->read = rs232_read;
	ttys[1]->controller.dev->write = rs232_write;
#endif
}

/* Read a string of the specified length from TTY */
void *tty_read(Device *tty, size_t len)
{
	return ((TTY_Device *) tty)->controller.buffer + strlen(((TTY_Device *) tty)->controller.buffer) - len;
}

/* Write a string of the specified length from TTY */
void tty_write(Device *tty, void *str, size_t len)
{
	Device *dev = ((TTY_Device *) tty)->controller.dev;
	dev->write(dev, str, len);
}
