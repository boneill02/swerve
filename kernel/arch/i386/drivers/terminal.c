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

#include "terminal.h"

#include "../portio.h"

#include <stdlib.h>
#include <string.h>

#define VGA_ENTRY_COLOR(fg,  bg) fg | bg << 4

size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color;
uint16_t *terminal_buffer = (uint16_t *) 0xB8000;

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

/* Sets the terminal color to the default value and clears it. */
void terminal_init(void)
{
	terminal_setcolor(VGA_ENTRY_COLOR(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
	terminal_clear();
}

/* Clears the terminal. */
void terminal_clear(void)
{
	size_t x, y;
	for (y = 0; y < VGA_HEIGHT; y++) {
		for (x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

/* Sets the color to a VGA color. */
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

/* Puts a character at a specific place (x,y) in the terminal. */
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

/* Puts a character at the current stored position in the terminal. */
void terminal_putchar(char c)
{
	switch (c) {
		case '\0':
			break;
		case '\n':
			terminal_row++;
			terminal_column = -1;
			break;
		/* TODO Add support for tabs. */
		default:
			terminal_putentryat((char) c, terminal_color, terminal_column, terminal_row);
	}

	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
} 

/*
 * Puts a null-terminated string at the current stored position in the terminal,
 * not printing the null character.
 */
void terminal_print(const char *data)
{
	size_t i;
	for (i = 0; i < strlen(data); i++) {
		terminal_putchar(data[i]);
	}
}

/*
 * Puts a null-terminated string at the current stored position in the terminal,
 * not printing the null character. A newline is printed after.
 */
void terminal_println(const char *data)
{
	terminal_print(data);
	terminal_putchar('\n');
}

/* Write wrapper for the Device type. */
void terminal_write(Device *dev, void *data, size_t size)
{
	terminal_print(data);
}

/* Enable the VGA mode cursor with a specified position. */
void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

/* Disable the VGA mode cursor. */
void terminal_disable_cursor(void)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

/* Place the VGA mode cursor at a specified position. */
void terminal_put_cursor_at(uint8_t x, uint8_t y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}
