#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
 
#define EOF (-1)

#ifdef __is_libk
void setty(int new_tty);
#endif
 
int printf(const char *__restrict, ...);
int putchar(int);
int puts(const char *);
 
#endif
