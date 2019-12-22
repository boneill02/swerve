/*
 * This file is part of the swerve libc.
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

#ifdef __is_libk
#include <tty.h>
static int current_tty = 1;

void setty(int new_tty)
{
	current_tty = new_tty;
}
#endif

int getchar(void)
{
	int c;
#ifdef __is_libk
	c = *((int *) ((Device *) ttys[current_tty])->read(NULL, 1));
#else
	/* TODO: syscall to implement putchar for userspace */
#endif
	return c;
}

int putchar(int ic)
{
	char c;
#ifdef __is_libk
	c = (char) ic;
	((Device *)ttys[current_tty])->write((Device *) ttys[current_tty], &c, sizeof(c));
#else
	/* TODO: syscall to implement putchar for userspace */
#endif
	return ic;
}
