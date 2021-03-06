#include <stdlib.h>
#include <gobject/gtype.h>
#include <gobject/gobject.h>

/* GObject constructor
 */
GObject *g_object_constructor(GType type, guint prop_count, GObjectConstructParam *construct_params) {
	puts("Parent Constructor");
	GObject *ret = (GObject *) g_type_create_instance(type);
	/*
         * TODO: handle constructor params
         */
	return ret;
}


/*
 * Initialser for ever gobject class
 */
void g_object_class_init(GObjectClass *self) {
	puts("Parent Class Init");
	self->constructor = g_object_constructor;
}


/*
 * The initialiser for every object
 */
void g_object_init(GObject *self) {
	self->ref_count = 1;
}

/*
 * The global gobject class
 */
static GObjectClass g_object_class;

/*
 * Get type information about GObject
 */
GType g_object_get_type() {
	GType ret = g_type_from_name("GObject");
	if (!ret) {
    		ret = g_type_fundamental_next();
    		GTypeInfo info;
    		info.class_size = sizeof(GObjectClass);
    		info.class_init = g_object_class_init;
    		info.instance_size = sizeof(GObject);
    		info.instance_init = g_object_init;
		g_type_register_fundamental(ret, "GObject", &info, NULL, 0);
	}
	// TODO:
	// ret.size = sizeof(GObject);
	// ret.class_init = (void (*)(gpointer)) g_object_class_init;
	// ret.klass = (gpointer) &g_object_class;
	// G_OBJECT_CLASS(ret.klass)->constructor = &g_object_constructor;
	// ret.init = g_object_init;
	// /*
 //         * Must be more than just an object
 //         * so don't need to keep track of
 //         * class init
 //         */
	// ret.done_class_init = NULL;
	return ret;
}

GObject *g_object_new(GType type, gchar const *names, ...) {
	gpointer klass = g_type_class_ref(type);
	GObject *ret = G_OBJECT_CLASS(klass)->constructor(type, 0, NULL);

	// GObject *ret = malloc(type.size);
	// if (!*type.done_class_init) {
	// 	((GObjectClass *)type.klass)->constructor = NULL;
	// 	type.class_init(type.klass);
	// 	*type.done_class_init=TRUE;
	// }
	// ret = ((GObjectClass *)type.klass)->constructor(type, 0, NULL);
	// type.init(ret);
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
