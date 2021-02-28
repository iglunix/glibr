#include <glib/gtypes.h>
#include <gobject/gtype.h>
#include <gobject/gboxed.h>

#include "gtypeintern.h"

GType g_boxed_get_type() {
	GType ret = g_type_from_name("GBoxed");
	if (!ret) {
		ret = g_type_fundamental_next();
		
		GTypeInfo info;
		info.class_size = 0;
		info.class_init = NULL;
		info.instance_size = 0;
		info.instance_init = NULL;
		g_type_register_fundamental(ret, "GBoxed", &info, NULL, 0);
	}
	return ret;
}

gpointer g_boxed_copy(GType g_boxed_type, gconstpointer src_boxed) {
	return g_type_intern_peek_boxed_extras_cpy(g_boxed_type)(src_boxed);
}

void g_boxed_free(GType g_boxed_type, gpointer boxed) {
	g_type_intern_peek_boxed_extras_free(g_boxed_type)(boxed);
}

GType g_boxed_type_register_static(gchar const *name, GBoxedCopyFunc cpyfunc, GBoxedFreeFunc freefunc) {
	GTypeInfo info;
	info.class_size = 0;
	info.class_init = NULL;
	info.instance_size = 0;
	info.instance_init = NULL;

	GType ret = g_type_register_static(G_TYPE_BOXED, name, &info, 0);
	g_type_intern_register_boxed_extras(ret, cpyfunc, freefunc);
	return ret;
}
