#include <stdlib.h>
#include <gobject/gtype.h>
#include <gobject/gobject.h>

/* GObject constructor
 */
GObject *g_object_constructor(GType type, guint prop_count, GObjectConstructParam *construct_params) {
	GObject *ret;
	/*
         * TODO: g_type_create_instance(type)
         */
	ret = (GObject *) malloc(type.size);
	/*
         * TODO: handle constructor params
         */
	return ret;
}


/*
 * Initialser for ever gobject class
 */
void g_object_class_init(GObjectClass *self) {
	self->constructor = g_object_constructor;
}


/*
 * The initialiser for every object
 */
void g_object_init(GObject *self) {

}

/*
 * The global gobject class
 */
static GObjectClass g_object_class;

/*
 * Get type information about GObject
 */
GType g_object_get_type() {
	GType ret;
	ret.size = sizeof(GObject);
	ret.class_init = g_object_class_init;
	ret.klass = (gpointer) &g_object_class;
	/*
         * Must be more than just an object
         * so don't need to keep track of
         * class init
         */
	ret.done_class_init = NULL;

	return ret;
}

GObject *g_object_new(GType type, gchar const *names, ...) {
	GObject *ret = malloc(type.size);
	if (!*type.done_class_init) {
		((GObjectClass *)type.klass)->constructor = NULL;
		type.class_init(type.klass);
		*type.done_class_init=TRUE;
	}
	((GObjectClass *)type.klass)->init(ret);
	if (((GObjectClass *)type.klass)->constructor) ((GObjectClass *)type.klass)->constructor(type, 0, NULL);
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
