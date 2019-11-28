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

#ifdef RS232_DRIVER
#ifndef RS232_H
#define RS232_H

#include <stddef.h>
#include "../device.h"

void rs232_init(void);
int rs232_received(void);
int rs232_getchar(void);
void rs232_getline(char *dest);

int rs232_is_transmit_empty(void);
void rs232_putchar(char);
void rs232_print(const char *str);
void rs232_println(const char *str);
void *rs232_read(Device *dev, size_t len);
void rs232_write(Device *dev, void *str, size_t size);

#endif
#endif
