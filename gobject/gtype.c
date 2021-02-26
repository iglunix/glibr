#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include <glib/gtypes.h>
#include <gobject/gtype.h>

/*
 * TODO:
 * GLOBAL TYPE REGISTRY
 * 
 * GQuark	g_type_qname ()
 * GType	g_type_next_base ()
 * gboolean	g_type_is_a ()
 * gpointer	g_type_class_ref ()
 * gpointer	g_type_class_peek ()
 * gpointer	g_type_class_peek_static ()
 * void	g_type_class_unref ()
 * gpointer	g_type_class_peek_parent ()
 * void	g_type_class_add_private ()
 * void	g_type_add_class_private ()
 * gpointer	g_type_interface_peek ()
 * gpointer	g_type_interface_peek_parent ()
 * gpointer	g_type_default_interface_ref ()
 * gpointer	g_type_default_interface_peek ()
 * void	g_type_default_interface_unref ()
 * GType *	g_type_interfaces ()
 * GType *	g_type_interface_prerequisites ()
 * void	g_type_set_qdata ()
 * gpointer	g_type_get_qdata ()
 * void	g_type_query ()
 * void	(*GInterfaceInitFunc) ()
 * void	(*GInterfaceFinalizeFunc) ()
 * gboolean	(*GTypeClassCacheFunc) ()
 * GType	g_type_register_dynamic ()
 * void	g_type_add_interface_static ()
 * void	g_type_add_interface_dynamic ()
 * void	g_type_interface_add_prerequisite ()
 * GTypePlugin *	g_type_get_plugin ()
 * GTypePlugin *	g_type_interface_get_plugin ()
 * GType	g_type_fundamental ()
 * GTypeInstance *	g_type_create_instance ()
 * void	g_type_free_instance ()
 * void	g_type_add_class_cache_func ()
 * void	g_type_remove_class_cache_func ()
 * void	g_type_class_unref_uncached ()
 * void	g_type_add_interface_check ()
 * void	g_type_remove_interface_check ()
 * void	(*GTypeInterfaceCheckFunc) ()
 * GTypeValueTable *	g_type_value_table_peek ()
 * void	g_type_ensure ()
 * guint	g_type_get_type_registration_serial ()
 * int	g_type_get_instance_count ()
 */

struct TypeRegistryNode {
	gchar const *name;
	/* 0 if fundamental */
	size_t parent_count;
	size_t *parents;
	size_t child_count;
	size_t *children;
};

/*
 * Type registry stored as a graph in a linear array with each node referencing
 * other elements in the array as parents and children
 */

static size_t next_free = 0;
static size_t type_allocated = 0;

/*
 * To keep track of what areas are initailised
 */
static uint8_t *type_registry_initialised = NULL;
static struct TypeRegistryNode *type_registry = NULL;

static void init_type(
	GType id,
	gchar const *name
) {
	while (id < type_allocated) {
		size_t old_allocated = type_allocated;
		type_allocated || (type_allocated += 1);
		type_allocated *= 2;
		type_registry = realloc(
			type_registry,
			sizeof(struct TypeRegistryNode) * type_allocated
		);
		type_registry_initialised = realloc(
    			type_registry_initialised,
    			type_allocated
    		);
		memset(type_registry_initialised + old_allocated, 0, type_allocated - old_allocated);
	}
	type_registry_initialised[id] = 1;
	type_registry[id].parent_count = 0;
	type_registry[id].parents = NULL;
	type_registry[id].child_count = 0;
	type_registry[id].children = NULL;
}

static GType next_free_type() {
	while (type_registry_initialised[next_free]) {
		next_free++;
	}
	return next_free;
}

/*
 * TODO: make use of `info`, `finfo` and `flags`
 */
GType g_type_register_fundamental(
	GType id,
	gchar const *type_name,
	const GTypeInfo *info,
	const GTypeFundamentalInfo *finfo,
	GTypeFlags flags
) {
	init_type(id, type_name);
	return id;
}

GType g_type_fundamental_next() {
	return next_free_type();
}

GType g_type_register_static(
	GType parent_type,
	gchar const *type_name,
	const GTypeInfo *info,
	GTypeFlags flags
) {
	GType ret = next_free_type();
	init_type(ret, type_name);
	type_registry[ret].parent_count = 1;
	type_registry[ret].parents = malloc(sizeof(GType) * 1);
	type_registry[ret].parents[0] = parent_type;
	return ret;
}

GType g_type_register_static_simple(
	GType parent_type,
	gchar const *type_name,
	guint class_size,
	GClassInitFunc class_init,
	guint instance_size,
	GInstanceInitFunc instance_init,
	GTypeFlags flags
) {
	return g_type_register_static(parent_type, type_name, NULL, 0);
}

/*
 * Deprecated
 */
void g_type_init() {

}

/*
 * Deprecated
 */
void g_type_init_with_debug_flags(GTypeDebugFlags not_used) {

}

gchar const *g_type_name(GType type) {
	return type_registry[type].name;
}

GType g_type_from_name(gchar const *name) {
	for (size_t i = 0; i < type_allocated; i++) {
		if (type_registry_initialised[i]
		 && !strcmp(name, g_type_name(i))) {
    			return i;
		}
	}
	return 0;
}

GType g_type_parent(GType type) {
	if (!type_registry_initialised[type]
	 || !type_registry[type].parent_count
	 || !type_registry[type].parents) {
		return 0;
	}
	return type_registry[type].parents[0];
}

guint g_type_depth(GType type) {
	GType parent = g_type_parent(type);
	if (parent) {
    		return g_type_depth(parent) + 1;
	} else {
    		return 1;
	}
}

GType *g_type_children(GType type, guint *count) {
	if (count) {
		*count = type_registry[type].child_count;
	}

	GType *ret = malloc(sizeof(GType) * (type_registry[type].child_count + 1));
	memcpy(ret, type_registry[type].children, type_registry[type].child_count);
	ret[type_registry[type].child_count] = 0;
	return ret;
}
