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

#ifndef DRIVERS_VGATEXT_H
#define DRIVERS_VGATEXT_H

#include "../device.h"

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void vgatext_clear(void);
void vgatext_disablecursor(void);
void vgatext_enablecursor(void);
void vgatext_init(void);
void vgatext_print(const char *);
void vgatext_println(const char *);
void vgatext_putcursorat(uint8_t, uint8_t, uint8_t, uint8_t);
void vgatext_putentryat(char, uint8_t, size_t, size_t);
void vgatext_putchar(char);
void vgatext_setcolor(uint8_t);
void vgatext_write(Device *, void *, size_t);

#endif
