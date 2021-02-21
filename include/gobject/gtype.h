#ifndef __G_TYPE_H__
#define __G_TYPE_H__

#include <glib.h>

/*
 * In GLib this is a single unique identifier
 * but that requires a global registry of types
 * 
 * I'll probably end up doing that for compatibility
 * and might clean up this messy struct
 * 
 * need to add "getters" for these fields to allow that
 */

typedef struct _GType {
	struct _GType (*parent_get_type)();
	gsize size;
	gpointer klass;
	gboolean *done_class_init;
	void (*class_init)(gpointer klass);
	void (*init)(gpointer obj);
} GType;

/*
 * base of every class
 */
typedef struct _GTypeClass {
	GType g_type;
} GTypeClass;

/*
 * base of every object constructed
 */
typedef struct _GTypeInstace {
	/*
         * All objects need to know what type they are
         */
	GTypeClass g_class;
} GTypeInstace;

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

GType g_object_get_type();
#define G_TYPE_OBJECT g_object_get_type()


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
	static void mod_obj_name##_class_init ( ModObjName##Class *klass ); \
	static void mod_obj_name##_init ( ModObjName *obj ); \
	static ModObjName mod_obj_name##_class; \
	static gboolean mod_obj_name##_done_class_init; \
	static gpointer mod_obj_name##_parent_class = &mod_obj_name##_class; \
	static void mod_obj_name##_class_intern_init(gpointer klass) { \
		GType parent_type = PARENT_TYPE; \
		parent_type.class_init(&((ModObjName##Class *) klass)->parent_class); \
		/* ((ModObjName##Class *) klass)->constructor = ((ModObjName##Class *) klass)->parent_class.constructor; */ \
		mod_obj_name##_parent_class = (gpointer) parent_type.klass; \
		mod_obj_name##_class_init((ModObjName##Class *)klass); \
	} \
	GType mod_obj_name##_get_type() { \
		GType ret; \
		ret.size=sizeof(ModObjName); \
		ret.done_class_init=&mod_obj_name##_done_class_init; \
		ret.klass=(gpointer) &mod_obj_name##_class; \
		ret.class_init=&mod_obj_name##_class_intern_init; \
		ret.init = mod_obj_name##_init; \
		return ret; \
	}

#endif
