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

#ifndef DRIVERS_TTY_H
#define DRIVERS_TTY_H

#define TAB_SIZE 4
#define MAX_TTYS 8

#include <stddef.h>
#include "../device.h"

struct tty_controller {
	int id;
	int cursor_x, cursor_y, cursor_status;
	Device *dev;
	char *buffer;
	size_t unwritten;
};

typedef struct {
	Device parent;
	struct tty_controller controller;
} TTY_Device;

TTY_Device *ttys[MAX_TTYS];

void tty_init(void);
void *tty_read(Device *, size_t);
void tty_write(Device *, void *, size_t);
void tty_update(Device *);

#endif
