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

#include <string.h>

int strcmp(const char *s1, const char *s2)
{
	int i;
	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
		if (s1[i] != s2[i])
			return s2[i] - s1[i];
	}

	return s2[i] - s1[i];
}
