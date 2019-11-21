#include "pmm.h"


unsigned long *pt = 0x00000010;

void *get_physaddr(void *virtaddr)
{
	unsigned long pdindex = (unsigned long) virtaddr >> 22;
	unsigned long ptindex = (unsigned long) virtaddr >> 12 & 0x03FF;

	unsigned long *pd = (unsigned long *)0xFFFFF000;
	((unsigned long *)0xFFC00000) + (0x400 * pdindex);

	return (void *)((pt[ptindex] & ~0xFFF) + ((unsigned long)virtaddr & 0xFFF));
}

void map_page(void *physaddr, void *virtualaddr, unsigned int flags)
{
	unsigned long pdindex = (unsigned long)virtualaddr >> 22;
	unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;
	unsigned long *pd = (unsigned long *)0xFFFFF000;
	unsigned long *pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
	pt[ptindex] = ((unsigned long)physaddr) | (flags & 0xFFF) | 0x01;
} 
