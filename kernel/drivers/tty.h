#ifndef DRIVERS_TTY_H
#define DRIVERS_TTY_H

#define TAB_SIZE 4
#define MAX_TTYS 16

#include <stddef.h>
#include "../device.h"

struct tty_controller {
	int id;
	int cursor_x, cursor_y, cursor_status;
	Device *dev;
	char *buffer;
};

typedef struct {
	Device parent;
	struct tty_controller controller;
} TTY_Device;

TTY_Device *ttys[MAX_TTYS];

void tty_init(void);
void *tty_read(Device *, size_t);
void tty_write(Device *, void *, size_t);
void tty_update(Device *);

#endif
