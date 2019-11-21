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

#include "kmalloc.h"
#include "../kmain.h"

#include <stddef.h>
#include <string.h>

struct MemNode {
	char free;
	void *ptr;
	size_t size;
	struct MemNode *next;
};

struct MemNode *top;

void kmeminit(void)
{
	top = KERN_MEMORY_BASE;
	memset(top, 0, sizeof(struct MemNode));
	top->ptr = PROC_MEMORY_BASE;
}

void *kmalloc(size_t size)
{
	struct MemNode *node = top;

	while (node->next != NULL) {
		node = node->next;
		if (node->size >= size) {
			return node->ptr;
		}
	}

	node->next = (struct MemNode *) node->ptr + sizeof(struct MemNode);
	node->next->ptr = node->ptr + node->size;
	node = node->next;
	memset(node, 0, sizeof(struct MemNode));
	node->size = size;
	return node->ptr;
}

void kfree(void *mem)
{
	struct MemNode *node = top;

	while (node->ptr != mem && node != NULL)
		node = node->next;

	return node;
}
