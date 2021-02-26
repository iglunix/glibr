#include <stdio.h>

gint g_vasprintf(gchar **string, gchar const *fmt, va_list args) {
	gint len;
	len = vas_printf(string, fmt, args);
	return len;
}
