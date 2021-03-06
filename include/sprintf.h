#ifndef _SPRINTF_H
#define _SPRINTF_H 

#include "types.h"
#include "stdarg.h"

char* itoa(int d, char* buf, int base);
char* utoa(u32 u, char* buf, int base);

int vsprintf(char* sbuf, const char* fmt, va_list args);
int vsnprintf(char* sbuf, size_t len, const char* fmt, va_list args);

int sprintf(char* buf, const char* fmt, ...);
int snprintf(char* buf, size_t len, const char* fmt, ...);

#endif
