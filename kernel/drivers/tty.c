#include "tty.h"

#include "terminal.h"

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
		((Device *)ttys[i])->read = tty_read;
		((Device *)ttys[i])->write = tty_write;
		((Device *)ttys[i])->update = tty_update;
	}
}

void *tty_read(Device *tty, size_t len)
{
	return ((TTY_Device *) tty)->controller.buffer + strlen(((TTY_Device *) tty)->controller.buffer) - len;
}

void tty_write(Device *tty, char *str, size_t len)
{
	strncpy(((TTY_Device *) tty)->controller.buffer, str, len);
	tty->update(tty);
}

void tty_update(Device *tty)
{
	terminal_print((char *) ((TTY_Device *) tty)->controller.buffer);
}
