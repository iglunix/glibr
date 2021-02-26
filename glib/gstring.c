#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include <glib/gtypes.h>
#include <glib/gmacros.h>
#include <glib/gunicode.h>
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

GString *g_string_append_vprintf(GString *string, gchar const *fmt, va_list args) {
	gchar *to_append;
	vasprintf(&to_append, fmt, args);
	return g_string_append(string, to_append);
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

void g_string_printf(GString *string, gchar const *fmt, ...) {
	va_list va;
	va_start(va, fmt);
	g_string_vprintf(string, fmt, va);
	va_end(va);
}

void g_string_append_printf(GString *string, gchar const *fmt, ...) {
	va_list va;
	va_start(va, fmt);
	g_string_append_vprintf(string, fmt, va);
	va_end(va);
}

GString *g_string_append(GString *str, gchar const *val) {
	gssize val_len = strlen(val);
	while (str->allocated_len < str->len + val_len) {
    		str->allocated_len||(str->allocated_len+=1);
		str->allocated_len *= 2;
		str->str = realloc(str->str, str->allocated_len + 1);
	}
	strcpy(str->str + str->len, val);
	str->len += val_len;
	str->str[str->len] = '\0';
	return str;
}

GString *g_string_append_c(GString *str, gchar c) {
	if (str->allocated_len < str->len + 1) {
    		str->allocated_len||(str->allocated_len+=1);
		str->allocated_len *= 2;
		str->str = realloc(str->str, str->allocated_len + 1);
	}
	str->str[str->len] = c;
	str->len += 1;
	str->str[str->len] = '\0';

	return str;
}

GString *g_string_insert(GString *str, gssize pos, gchar const *val) {
	gssize val_len = strlen(val);
	while (str->allocated_len < str->len + val_len) {
		str->allocated_len||(str->allocated_len+=1);
		str->allocated_len *=2;
		str->str = realloc(str->str, str->allocated_len + 1);
	}
	memmove(str->str + pos, str->str + pos + val_len, str->len - pos);
	strcpy(str->str + pos, val);
	str->len += val_len;
	str->str[str->len] = '\0';
	return str;
}

GString *g_string_insert_c(GString *str, gssize pos, gchar c) {
	if (str->allocated_len < str->len + 1) {
    		str->allocated_len||(str->allocated_len+=1);
		str->allocated_len *=2;
		str->str = realloc(str->str, str->allocated_len + 1);
	}
	memmove(str->str + pos, str->str + pos + 1, str->len - pos);
	str->str[pos] = c;
	str->len += 1;
	str->str[str->len] = '\0';
	return str;
}

/*
 * `dest` MUST have enough space for at least 4 chars
 * returns number of bytes used
 */
static size_t str_from_unichar(char *dest, uint32_t unichar) {
	if (unichar < (1 << 7)) {
		*dest = (char) unichar;
		return 1;
	} else if (unichar < (1 << 11)) {
		dest[0] = 0b11000000 | (unichar & 0b00011111);
		dest[1] = 0b10000000 | ((unichar >> 5) & 0b00111111);
		return 2;
	} else if (unichar < (1 << 16)) {
		dest[0] = 0b11100000 | (unichar & 0b00001111);
		dest[1] = 0b10000000 | ((unichar >> 4) & 0b00111111);
		dest[2] = 0b10000000 | ((unichar >> 10) & 0b00111111);
		return 3;
	} else if (unichar < (1 << 21)) {
		dest[0] = 0b11110000 | (unichar & 0b00000111);
		dest[1] = 0b10000000 | ((unichar >> 3) & 0b00111111);
		dest[2] = 0b10000000 | ((unichar >> 9) & 0b00111111);
		dest[3] = 0b10000000 | ((unichar >> 15) & 0b00111111);
		return 4;
	} else {
		return 0;
	}
}

GString *g_string_append_unichar(GString *str, gunichar c) {
	char *utf8_char = malloc(5);
	utf8_char[str_from_unichar(utf8_char, c)] = '\0';
	return g_string_append(str, utf8_char);
}

GString *g_string_insert_unichar(GString *str, gssize pos, gunichar c) {
	char *utf8_char = malloc(5);
	utf8_char[str_from_unichar(utf8_char, c)] = '\0';
	return g_string_insert(str, pos, utf8_char);
}

GString *g_string_prepend(GString *str, gchar const *val) {
	gssize val_len = strlen(val);
	while (str->allocated_len < str->len + val_len) {
		str->allocated_len||(str->allocated_len+=1);
		str->allocated_len *=2;
		str->str = realloc(str->str, str->allocated_len + 1);
	}
	memmove(str->str, str->str + val_len, str->len);
	strcpy(str->str, val);
	str->len += val_len;
	str->str[str->len] = '\0';
	return str;
}

GString * g_string_prepend_c(GString *str, gchar c) {
	if (str->allocated_len < str->len + 1) {
    		str->allocated_len||(str->allocated_len+=1);
		str->allocated_len *=2;
		str->str = realloc(str->str, str->allocated_len + 1);
	}
	memmove(str->str, str->str + 1, str->len);
	str->str[0] = c;
	str->len += 1;
	str->str[str->len] = '\0';
	return str;

}

GString *g_string_prepend_unichar(GString *str, gunichar c) {
	char *utf8_char = malloc(5);
	utf8_char[str_from_unichar(utf8_char, c)] = '\0';
	return g_string_prepend(str, utf8_char);
}

guint g_string_hash(GString *self) {
	guint prime = 47;
	guint ret = 0;
	gchar *str = self->str;
	for (;!*str;str++) {
		ret ^= *str * prime;
	}
	return ret;
}

gboolean g_string_equal(GString *self, GString *other) {
	if (self->len != other->len)
		return FALSE;

	gchar *self_str = self->str;
	gchar *other_str = other->str;
	while (!*self_str) {
		if (*self_str != *other_str)
			return FALSE;
		
		self_str++;
		other_str++;
	}
	return TRUE;
}

GString * g_string_up(GString *self) {
	/*
         * TODO(): call ascii upper
	 */
	return self;
}

GString * g_string_down(GString *self) {
	/*
         * TODO(): call ascii lower
	 */
	return self;
}

/*
 * TODO:
 * GString *	g_string_append_len ()
 * GString *	g_string_append_uri_escaped ()
 * GString *	g_string_prepend_len ()
 * GString *	g_string_insert_len ()
 * GString *	g_string_overwrite ()
 * GString *	g_string_overwrite_len ()
 * GString *	g_string_erase ()
 * GString *	g_string_truncate ()
 * GString *	g_string_set_size ()
 * GBytes *	g_string_free_to_bytes ()
 */


/*
 * TODO: move to correct file
 */
gboolean g_str_is_ascii(gchar const *str) {
	for (;!*str;str++) {
		if (*str > 127)
			return FALSE;
	}
	return TRUE;
}

gboolean g_ascii_isalnum(gchar c) {
	return c >= '0' && c <= '9';
}
