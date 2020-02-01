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

#include "vgatext.h"

#include "../portio.h"

#include <stdlib.h>
#include <string.h>

#define VGA_ENTRY_COLOR(fg,  bg) fg | bg << 4

size_t vgatext_row = 0, vgatext_column = 0;
uint8_t vgatext_color;
uint16_t *vgatext_buffer = (uint16_t *) 0xb8000;

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

/*
 * Generates a VGA entry by combining the character that is set to be printed
 * and the color that character should be. This can probably be implemented
 * as a preprocessor macro.
 *
 * TODO Maybe we should make this a preprocessor macro.
 */
static uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

/* Sets the color to the default value and clears it. */
void vgatext_init(void)
{
	vgatext_setcolor(VGA_ENTRY_COLOR(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
	vgatext_clear();
}

/* Clears the screen. */
void vgatext_clear(void)
{
	size_t x, y;
	for (y = 0; y < VGA_HEIGHT; y++) {
		for (x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			vgatext_buffer[index] = vga_entry(' ', vgatext_color);
		}
	}
}

/* Sets the color to a VGA color. */
void vgatext_setcolor(uint8_t color)
{
	vgatext_color = color;
}

/* Puts a character at a specific place (x,y). */
void vgatext_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	vgatext_buffer[index] = vga_entry(c, color);
}

/* Puts a character at the current stored position. */
void vgatext_putchar(char c)
{
	switch (c) {
		case '\0':
			break;
		case '\n':
			vgatext_row++;
			vgatext_column = -1;
			break;
		/* TODO Add support for tabs. */
		default:
			vgatext_putentryat((char) c, vgatext_color, vgatext_column,
					vgatext_row);
	}

	if (++vgatext_column == VGA_WIDTH) {
		vgatext_column = 0;
		if (++vgatext_row == VGA_HEIGHT)
			vgatext_row = 0;
	}
} 

/*
 * Puts a null-terminated string at the current stored position, not printing
 * the null character.
 */
void vgatext_print(const char *data)
{
	size_t i;
	for (i = 0; i < strlen(data); i++) {
		vgatext_putchar(data[i]);
	}
}

/*
 * Puts a null-terminated string at the current stored position, not printing
 * the null character. A newline is printed after.
 */
void vgatext_println(const char *data)
{
	vgatext_print(data);
	vgatext_putchar('\n');
}

/* write() wrapper for the Device type. */
void vgatext_write(Device *dev, void *data, size_t size)
{
	/* this could use vgatext_print(), but it may not be null terminated */
	for (int i = 0; i < size; i++)
		vgatext_putchar(((char *) data)[i]);
}

/* Enable the VGA cursor. */
void vgatext_enablecursor(void)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0));

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0));
}

/* Disable the VGA mode cursor. */
void vgatext_disablecursor(void)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

/* Place the VGA mode cursor at a specified position. */
void vgatext_putcursorat(uint8_t x_start, uint8_t y_start, uint8_t x_end,
		uint8_t y_end)
{
	uint16_t cursor_start = y_start * VGA_WIDTH + x_start;
	uint16_t cursor_end = y_end * VGA_WIDTH + x_end;

	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}
