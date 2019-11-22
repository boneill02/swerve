#include <string.h>

char *strcpy(char * restrict dst, const char * restrict src)
{
	strncpy(dst, src, strlen(src));
	return dst;
}
