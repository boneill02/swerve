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

#include "rs232.h"

#include "../portio.h"

#define PORT 0x3f8   /* COM1 */
 
void rs232_init()
{
	outb(PORT + 1, 0x00);
	outb(PORT + 3, 0x80);
	outb(PORT + 0, 0x03);
	outb(PORT + 1, 0x00);
	outb(PORT + 3, 0x03);
	outb(PORT + 2, 0xC7);
	outb(PORT + 4, 0x0B);
}

int rs232_received()
{
	return inb(PORT + 5) & 1;
}
 
char rs232_getchar()
{
	while (rs232_received() == 0);
 
	return inb(PORT);
}

void rs232_getline(char *str)
{
	int receiving = 1, i = 0;

	while (receiving) {
		while (rs232_received() == 0);

		str[i] = inb(PORT);
		if (str[i] == '\n' || str[i] == '\0')
			receiving = 0;

		i++;
	}
	str[i] = '\0';
}

int rs232_is_transmit_empty()
{
	return inb(PORT + 5) & 0x20;
}
 
void rs232_putchar(char a)
{
	while (rs232_is_transmit_empty() == 0);
	outb(PORT, a);
}

void rs232_print(const char *str)
{
	int i = 0;
	while (str[i] != '\0') {
		rs232_putchar(str[i]);
		i++;
	}
}

void rs232_println(const char *str)
{
	rs232_print(str);
	rs232_putchar('\n');
}
