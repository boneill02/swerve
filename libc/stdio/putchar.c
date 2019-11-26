#include <stdio.h>

#ifdef __is_libk
#include <tty.h>
static int current_tty = 1;

void setty(int new_tty)
{
	current_tty = new_tty;
}
#endif

int getchar(void)
{
	int c;
#ifdef __is_libk
	c = *((int *) ((Device *) ttys[current_tty])->read(NULL, 1));
#else
	/* TODO: syscall to implement putchar for userspace */
#endif
	return c;
}

int putchar(int ic)
{
	char c;
#ifdef __is_libk
	c = (char) ic;
	((Device *)ttys[current_tty])->write((Device *) ttys[current_tty], &c, sizeof(c));
#else
	/* TODO: syscall to implement putchar for userspace */
#endif
	return ic;
}
