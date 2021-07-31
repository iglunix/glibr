#include <stdio.h>
#include <glib/gtypes.h>

void g_print(gchar const *fmt, ...);

#define g_debug(fmt, ...) fprintf(stderr, ##__VA_ARGS__)
