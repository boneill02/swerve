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

#include "kmain.h"

#include <stdbool.h>

#include "drivers/tty.h"
#include "drivers/serial/rs232.h"
#include "mm/wmalloc.h"

const char *version_info = "swerve-" VERSION "-" ARCH;

/* FIXME put in libc */
bool streq(const char *s1, const char *s2)
{
	int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0') {
		if (s1[i] != s2[i])
			return false;
		i++;
	} 
	if (s1[i] != '\0' || s2[i] != '\0')
		return false;

	return true;
}

void rs232_shell(void)
{
	char *input;
	int i;
	char c;
	bool running, reading;

	running = true;
	while (running) {
		input = wmalloc(256);
		i = 0;
		reading = true;
		rs232_print("$ ");
		while (reading) {
			input[i] = rs232_getchar();
			rs232_putchar(input[i]);
			if (input[i] == '\r') {
				input[i] = '\0';
				rs232_putchar('\n');
				reading = false;
			}
			i++;
		}

		if (streq(input, "help")) {
			rs232_println("commands: help, exit, version");
		} else if (streq(input, "exit")) {
			running = false;
		} else if (streq(input, "version")) {
			rs232_println(version_info);
		} else {
			rs232_println("unrecognized command. type help for command list");
		}
	}

	rs232_println("Bye!");
}

void kmain(void)
{
	int i;

	/* initialize drivers */
	rs232_initialize();
	if (DEBUG)
		rs232_println("* Initialized RS-232 driver");

	terminal_initialize();
#ifdef DEBUG
	rs232_println("* Initialized VGA mode driver");
#endif

	/* print welcome */
	terminal_print("Version: ");
	terminal_println(version_info);
	terminal_disable_cursor();
#ifdef DEBUG
	rs232_println("* Printed version info to VGA");
#endif

	/* initialize allocator */
	wminit(KERN_MEMORY_BASE, KERN_MEMORY_CEILING);
#ifdef DEBUG
	rs232_println("* Initialized watermark memory allocator");
#endif

	/* start RS-232 shell */
#ifdef DEBUG
	rs232_println(". Starting RS-232 shell");
#endif
	rs232_shell();
}
