#include <stdlib.h>
#include <gobject/gobject.h>

GObject *g_object_new(GType type, gchar const *names, ...) {
	GObject *ret = malloc(type.size);
	if (!*type.done_class_init) {
/*		type.klass->constructor = NULL;*/
		type.class_init(type.klass);
		*type.done_class_init=TRUE;
	}
/*	if (type.klass->constructor) type.klass->constructor();*/
	type.init(ret);
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
