#ifndef _STDLIB_H
#define _STDLIB_H 1
 
#include <sys/cdefs.h>
#include <stddef.h>

#define PROC_MEMORY_BASE    0xC0000000
#define PROC_MEMORY_CEILING 0xFFFFFED8
#define KERN_MEMORY_BASE    0x10000
#define KERN_MEMORY_CEILING 0xBFFFFFFF
 
#ifdef __is_libk
void mem_init(void);
#endif

void *malloc(size_t size);
void free(void *ptr);
void abort(void);
 
#endif
