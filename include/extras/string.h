#ifndef _EXTRAS_STRING_H
#define _EXTRAS_STRING_H

#include <stdlib.h>

char *strcat(char *dest, const char *src);
int strncmp(const char *s1, const char *s2, size_t n);
size_t strlen(const char *str);
char *strchr(const char *s, int c);

#endif