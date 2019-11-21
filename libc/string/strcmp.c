#include <string.h>

int strcmp(const char *s1, const char *s2)
{
	int i;
	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
		if (s1[i] != s2[i])
			return s2[i] - s1[i];
	}

	return s2[i] - s1[i];
}
