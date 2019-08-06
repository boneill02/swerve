#include "wmalloc.h"

#include <stdbool.h>

size_t wm_base, wm_top, wm_ceiling;
bool wm_initialized = false;

void
wminit(size_t base, size_t ceiling)
{
	wm_base = base;
	wm_top = base;
	wm_ceiling = ceiling;

	wm_initialized = true;
}

void *
wmalloc(size_t num)
{
	if (wm_initialized && (wm_top + num) < wm_ceiling) {
		void *mem = &wm_top;
		wm_top += num;
		return mem;
	}
	return NULL;

}
