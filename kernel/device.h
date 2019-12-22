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

#ifndef DEVICE_H
#define DEVICE_H

#include <stddef.h>

/*
 * This is supposed to make device drivers act like files. You can read from and
 * write to these devices like one would with any file on a Unix-like system.
 */
struct device_s {
	void *(*read)(struct device_s *, size_t);
	void (*write)(struct device_s *, void *, size_t);
};

typedef struct device_s Device;

#endif
