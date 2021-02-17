#include <stdlib.h>
#include <string.h>

#include <glib/gtypes.h>
#include <glib/gstring.h>

GString *g_string_new(gchar const *str) {
	GString *ret = malloc(sizeof(GString));
	if (str) {
		ret->len=strlen(str);
		ret->str=malloc(ret->len+1);
		strncpy(ret->str, str,strlen(str));
	} else {
		ret->len=0;
		ret->str=NULL;
	}
	ret->allocated_len=ret->len;
	return ret;
};

gchar *g_string_free(GString *str, gboolean free_segment) {
	gchar *ret = str->str;
	free(str);
	if (free_segment) {
		free(ret);
		return NULL;
	} else {
		return ret;
	}
};
