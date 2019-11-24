#include <stdio.h>

#ifdef __is_libk
#include <tty.h>
static int current_tty = 1;

void setty(int new_tty)
{
	current_tty = new_tty;
}
#endif

int putchar(int ic)
{
#ifdef __is_libk
	char c = (char) ic;
	((Device *)ttys[current_tty])->write((Device *) ttys[current_tty], &c, sizeof(c));
#else
	/* TODO: syscall to implement putchar for userspace */
#endif
	return ic;
}
