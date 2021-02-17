#ifndef __G_STRING_H__
#define __G_STRING_H__
#include "gtypes.h"

typedef struct _GString {
	gchar *str;
	gsize len;
	gsize allocated_len;
} GString;

GString *g_string_new(gchar const *str);
gchar *g_string_free(GString *str, gboolean free_int);

#endif
