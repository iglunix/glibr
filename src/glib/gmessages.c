#include <stdio.h>
#include <stdarg.h>
#include "gtypes.h"

void g_print(gchar const *fmt, ...) {
	va_list va;
	va_start(va, fmt);
	vprintf(fmt, va);
	va_end(va);
}
