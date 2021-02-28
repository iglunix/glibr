#ifndef __G_TYPE_H__
#define __G_TYPE_H__

#include <glib.h>
#include <stddef.h>

/*
 * GType is just an index in the global type registry
 */

typedef size_t GType;

#include <gobject/gvalue.h>
#include <gobject/gvaluecollector.h>

typedef enum _GTypeDebugFlags {
	G_TYPE_DEBUG_NONE,
	G_TYPE_DEBUG_OBJECT,
	G_TYPE_DEBUG_SIGNALS,
	G_TYPE_DEBUG_INSTANCE_COUNT,
	G_TYPE_DEBUG_MASK
} GTypeDebugFlags;

typedef enum GTypeFlags {
	G_TYPE_FLAG_ABSTRACT,
	G_TYPE_FLAG_VALUE_ABSTRACT
} GTypeFlags;


/*
 * base of every class
 */
typedef struct _GTypeClass {
	GType g_type;
} GTypeClass;

/*
 * base of every object constructed
 */
typedef struct _GTypeInstance {
	/*
         * All objects need to know what type they are
         */
	GTypeClass *g_class;
} GTypeInstance;

/*
 * base of all interfaces
 */
typedef struct _GTypeInterface {
	/*
         * the type information
         */
	GType g_type;
	/*
         * Keeps track of child type
         * I'm sure the reasoning for this will come clear later
         */
	GType g_instance_type;
} GTypeInterface;

typedef void (*GBaseInitFunc)(gpointer g_class);
typedef void (*GBaseFinalizeFunc)(gpointer g_class);
typedef void (*GClassInitFunc)(gpointer g_class);
typedef void (*GClassFinalizeFunc)(gpointer g_class);
typedef void (*GInstanceInitFunc)(GTypeInstance *instance, gpointer g_class);

typedef struct _GTypeValueTable {
	void (*value_init)(GValue *value);
	void (*value_free)(GValue *value);
	void (*value_copy)(GValue const *src_value, GValue *dest_value);

	gpointer (*value_peek_pointer)(GValue const *value);
	gchar const *collect_format;
	gchar *(*collect_value) (GValue *, guint, GTypeCValue, guint);

	gchar const *lcopy_format;
	gchar *(*lcopy_value) (const GValue *, guint, GTypeCValue, guint);
} GTypeValueTable;

typedef struct _GTypeInfo {
	guint16 class_size;

	GBaseInitFunc base_init;
	GBaseFinalizeFunc base_finalize;

	GClassInitFunc class_init;
	GClassFinalizeFunc class_finalize;
	gconstpointer class_data;

	guint16 instance_size;
	guint16 n_preallocs;
	GInstanceInitFunc instance_init;

	const GTypeValueTable *value_table;
} GTypeInfo;

typedef enum _GTypeFundamentalFlags {
	G_TYPE_FLAG_CLASSED,
	G_TYPE_FLAG_INSTANTIATABLE,
	G_TYPE_FLAG_DERIVABLE,
	G_TYPE_FLAG_DEEP_DERIVABLE
} GTypeFundamentalFlags;

typedef struct _GTypeFundamentalInfo {
	GTypeFundamentalFlags type_flags;
} GTypeFundamentalInfo;

/*typedef struct _GType {
	struct _GType (*parent_get_type)();
	gchar const *name;
	gsize size;
	gpointer klass;
	gboolean *done_class_init;
	void (*class_init)(gpointer klass);
	void (*init)(gpointer obj);
} GType;*/



GType g_object_get_type();
#define G_TYPE_OBJECT g_object_get_type()
GType g_boxed_get_type();
#define G_TYPE_BOXED g_boxed_get_type()


/*
 * HACK: Glib has a typechecking function here; I can't be bothered with that
 */
#define G_TYPE_CHECK_CLASS_CAST(g_class, g_type, c_type) ((c_type *) g_class)

#define G_DECLARE_FINAL_TYPE(ModObjName, mod_obj_name, MOD, OBJ_NAME, SuperName) \
	GType mod_obj_name##_get_type(); \
	typedef struct _##ModObjName ModObjName; \
	typedef struct { \
		SuperName##Class parent_class; \
	} ModObjName##Class;
	//TODO AUTOPTR_CHAINUP

#define G_DEFINE_TYPE(ModObjName, mod_obj_name, PARENT_TYPE) \
	G_DEFINE_TYPE_EXTENDED(ModObjName, mod_obj_name, PARENT_TYPE, 0, {};)

#define G_DEFINE_TYPE_EXTENDED(ModObjName, mod_obj_name, PARENT_TYPE, FLAGS, CUSTOM_CODE) \
	static void mod_obj_name##_init(ModObjName *self); \
	static void mod_obj_name##_class_init(ModObjName##Class *klass); \
	static gpointer mod_obj_name##_parent_class = NULL; \
	static gint ModObjName##_private_offset; \
	static void mod_obj_name##_class_intern_init(gpointer klass) { \
		mod_obj_name##_parent_class = g_type_class_peek_parent(klass); \
		mod_obj_name##_class_init((ModObjName *) klass); \
	} \
	GType mod_obj_name##_get_type() { \
		GType ret = g_type_from_name("ModObjName"); \
		if (!ret) { \
			ret = g_type_register_static_simple( \
				PARENT_TYPE, \
				"ModObjName", \
				sizeof(ModObjName##Class), \
				(GClassInitFunc) mod_obj_name##_class_intern_init, \
				sizeof(ModObjName), \
				(GInstanceInitFunc) mod_obj_name##_init, \
				FLAGS \
			); \
			CUSTOM_CODE; \
		} \
		return ret; \
	} \

#endif

GType g_type_fundamental_next();

GType g_type_register_fundamental(GType, gchar const *, const GTypeInfo *, const GTypeFundamentalInfo *, GTypeFlags);
GType g_type_register_static(GType, gchar const *, const GTypeInfo *, GTypeFlags);
GType g_type_register_static_simple(GType, gchar const *, guint, GClassInitFunc, guint, GInstanceInitFunc, GTypeFlags);

void g_type_int();
void g_type_init_with_debug_flags();

gchar const *g_type_name(GType);
GType g_type_from_name(gchar const *);

GType g_type_parent(GType);
guint g_typ_depth(GType);
GType *g_type_children(GType, guint *);

gboolean g_type_is_a(GType, GType);

gpointer g_type_class_ref(GType);
gpointer g_type_class_peek(GType);
gpointer g_type_class_peek_static(GType);
void g_type_class_unref(gpointer);
gpointer g_type_class_peek_parent(gpointer g_class);
GTypeInstance *g_type_create_instance(GType);

void g_type_ensure(GType);

