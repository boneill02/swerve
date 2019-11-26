#include "tty.h"

#include "terminal.h"
#include "rs232.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tty_init(void)
{
	for (int i = 0; i < MAX_TTYS; i++) {
		ttys[i] = malloc(sizeof(TTY_Device));
		ttys[i]->controller.cursor_x = 0;
		ttys[i]->controller.cursor_y = 0;
		ttys[i]->controller.cursor_status = 1;
		ttys[i]->controller.buffer = malloc(8192);
		ttys[i]->controller.unwritten = 0;
		ttys[i]->controller.dev = NULL;
		((Device *)ttys[i])->read = tty_read;
		((Device *)ttys[i])->write = tty_write;
	}

	/* Special TTYs */
	ttys[0]->controller.dev = malloc(sizeof(Device));
	ttys[0]->controller.dev->write = terminal_write;

	ttys[1]->controller.dev = malloc(sizeof(Device));
	ttys[1]->controller.dev->read = rs232_read;
	ttys[1]->controller.dev->write = rs232_write;
}

void *tty_read(Device *tty, size_t len)
{
	return ((TTY_Device *) tty)->controller.buffer + strlen(((TTY_Device *) tty)->controller.buffer) - len;
}

void tty_write(Device *tty, void *str, size_t len)
{
	/* TODO fix so terminal and RS-232 work elegantly */
	Device *dev = ((TTY_Device *) tty)->controller.dev;
	dev->write(dev, str, len);
}
