#include <stdio.h>

#ifdef __is_libk
#include <tty.h>
#endif

int putchar(int ic)
{
#ifdef __is_libk
	char c = (char) ic;
	((Device *)ttys[0])->write((Device *) ttys[0], &c, sizeof(c));
#else
	/* TODO: syscall to implement putchar for userspace */
#endif
	return ic;
}
