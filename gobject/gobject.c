#include <stdlib.h>
#include <gobject/gobject.h>

GObject *g_object_new(GType type, gchar const *names, ...) {
	GObject *ret = malloc(type.size);
	if (!*type.done_class_init) {
		((GObjectClass *)type.klass)->constructor = NULL;
		type.class_init(type.klass);
		*type.done_class_init=TRUE;
	}
	type.init(ret);
	if (((GObjectClass *)type.klass)->constructor) ((GObjectClass *)type.klass)->constructor();
	return ret;
}

gpointer g_object_ref(gpointer object) {
	/*
         *  I'm guessing this updates the reference count
         */
	return object;
}

void g_object_unref(gpointer object) {
	/*
         *  I'm guessing this updates the reference count
         */
}
