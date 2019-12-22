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

#ifndef _STDLIB_H
#define _STDLIB_H 1
 
#include <sys/cdefs.h>
#include <stddef.h>

#define PROC_MEMORY_BASE    0xC0000000
#define PROC_MEMORY_CEILING 0xFFFFFED8
#define KERN_MEMORY_BASE    0x10000
#define KERN_MEMORY_CEILING 0xBFFFFFFF
 
#ifdef __is_libk
void mem_init(void);
#endif

void *malloc(size_t size);
void free(void *ptr);
void abort(void);
 
#endif
