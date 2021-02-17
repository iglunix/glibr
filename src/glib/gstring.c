#include <stdlib.h>
#include <string.h>

#include "gtypes.h"
#include "gstring.h"

GString *g_string_new(gchar const *str) {
	GString *ret = malloc(sizeof(ret));
	ret->len=strlen(str);
	ret->str=malloc(ret->len+1);
	ret->allocated_len=ret->len;
	strncpy(ret->str, str,strlen(str));
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
