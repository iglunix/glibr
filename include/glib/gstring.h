#ifndef __G_STRING_H__
#define __G_STRING_H__

#include <stdarg.h>
#include <glib/gtypes.h>
#include <glib/gunicode.h>

typedef struct _GString {
	gchar *str;
	gsize len;
	gsize allocated_len;
} GString;

GString *g_string_new(gchar const *str);
GString *g_string_new_len(gchar const *str, gssize);
GString *g_string_sized_new(gssize);
GString *g_string_vprintf(GString *self, gchar const *fmt, va_list);
GString *g_string_assign(GString *lhs, gchar const *rhs);
GString *g_string_append(GString *, gchar const *);
gchar *g_string_free(GString *str, gboolean free_int);

#endif
