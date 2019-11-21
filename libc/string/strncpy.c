#include <string.h>

char *strncpy(char * restrict dst, const char * restrict src, size_t size)
{
	memcpy(dst, src, size);
	dst[size] = '\0';
	return dst;
}
