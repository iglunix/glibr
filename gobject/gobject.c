#include <stdlib.h>
#include <gobject/gobject.h>

GObject *g_object_new(GType type, gchar const *names, ...) {
	GObject *ret = malloc(type.size);
	if (!*type.done_class_init) {
		type.class_init(NULL);
		*type.done_class_init = TRUE;
	}
	type.init(ret);
	return ret;
}
