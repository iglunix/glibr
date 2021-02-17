#include <stdio.h>
#include <stdarg.h>
#include <glib/gtypes.h>
#include <glib/gmessages.h>

void g_print(gchar const *fmt, ...) {
	va_list va;
	va_start(va, fmt);
	vprintf(fmt, va);
	va_end(va);
}
