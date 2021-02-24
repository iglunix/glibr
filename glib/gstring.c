#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

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
		return NULL;
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
	if (string->allocated_len < strlen(src)) {
		string->allocated_len = strlen(src);
		string->str = realloc(string->str, strlen(src) + 1);
	}
	string->len = strlen(src);
	strncpy(string->str, src, string->len);
	return string;
}

GString *g_string_vprintf(GString *string, gchar const *fmt, va_list args) {
	free(string->str);
	string->len = vasprintf(&string->str, fmt, args);
	string->allocated_len = string->len;
	return string;
}

/*
 * TODO: actually append?
 */
GString *g_string_append_vprintf(GString *string, gchar const *fmt, va_list args) {
	gchar *to_append;
	vasprintf(&to_append, fmt, args);
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
