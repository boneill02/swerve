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

#include "../device.h"
#include "rs232.h"
#include "../portio.h"

#include <stdlib.h>

#define PORT 0x3f8   /* COM1 */

void rs232_init();
int rs232_received();
int rs232_getchar();
void rs232_getline(char *str);
int rs232_is_transmit_empty();
void rs232_putchar(char a);
void rs232_print(const char *str);
void rs232_println(const char *str);
void *rs232_read(Device *dev, size_t len);
void rs232_write(Device *dev, void *str, size_t len);

#ifdef RS232_DRIVER

/* Initialize RS-232 device */
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

/* Check if there is anything waiting in the buffer */
int rs232_received()
{
	return inb(PORT + 5) & 1;
}
 
/* Get the next character in the buffer */
int rs232_getchar()
{
	while (rs232_received() == 0); 
	return inb(PORT);
}

/*
 * Put a line of text in the specified string. There are no safety mechanisms
 * here to prevent against writing to other memory, so be careful. I should fix
 * this.
 *
 * FIXME Add max length parameter for this function
 */
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

/*
 * Check if any output is currently being processed by the device (e.g. the
 * device is busy).
 */
int rs232_is_transmit_empty()
{
	return inb(PORT + 5) & 0x20;
}
 
/* Send a character to the device */
void rs232_putchar(char a)
{
	while (rs232_is_transmit_empty() == 0);
	outb(PORT, a);
}

/*
 * Print a null-terminated string to the device (not printing the null
 * character).
 */
void rs232_print(const char *str)
{
	int i = 0;
	while (str[i] != '\0') {
		rs232_putchar(str[i]);
		i++;
	}
}

/*
 * Print a null-terminated string to the device (not printing the null
 * character) and put a newline after. This is just for convenience as calls
 * like this may be performed often.
 */
void rs232_println(const char *str)
{
	rs232_print(str);
	rs232_putchar('\n');
}

/*
 * 	Read wrapper for the Device type. Allows for this driver to be used as a
 * 	Device.
 */
void *rs232_read(Device *dev, size_t len)
{
	int *res = malloc(len * sizeof(int));
	for (int i = 0; i < len; i++)
		res[i] = rs232_getchar();
	return (void *) res;
}

/*
 * 	Write wrapper for the Device type. Allows for this driver to be used as a
 * 	Device.
 */
void rs232_write(Device *dev, void *str, size_t len)
{
	for (int i = 0; i < len; i++)
		rs232_putchar(((char *) str)[i]);
}

#endif
