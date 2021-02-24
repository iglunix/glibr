#include <stdlib.h>
#include <string.h>

#include <glib/gtypes.h>
#include <glib/gstring.h>

GString *g_string_new(gchar const *str) {
	GString *ret = malloc(sizeof(GString));
	if (str) {
		ret->len=strlen(str);
		ret->str=malloc(ret->len+1);
		strncpy(ret->str, str, ret->len);
	} else {
		ret->len=0;
		ret->str=NULL;
	}
	ret->allocated_len=ret->len;
	return ret;
};

GString *g_string_new_len(gchar const *str, gssize len) {
	if (!str) {
		return NULL
	}
	GString *ret = malloc(sizeof(GString));
	ret->len = len;
	ret->str = malloc(ret->len + 1);
	strncpy(ret->str, str, ret->len);
	ret->str[ret->len] = '\0';
	ret->allocated_len=ret->len;
	return ret;
}

GString *g_string_sized_new(gssize size) {
	GString *ret = malloc(sizeof(GString));
	ret->len = 0;
	ret->str = malloc(size);
	ret->allocated_len = 0;
	return ret;
}

GString *g_string_assign(GString *string, gchar const *src) {
	if (ret->allocated_len < strlen(src)) {
		ret->allocated_len = strlen(src);
		ret->str = realloc(ret->str, strlen(src) + 1);
	}
	ret->len = strlen(src);
	strncpy(ret->str, str, ret->len);
}

/*
 * TODO: expand string?
 */
GString *g_string_vprintf(GString *string, gchar const *fmt, va_list args) {
	vsprintf(string->str, fmt, args);
	return string;
}

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
