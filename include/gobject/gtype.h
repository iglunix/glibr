#ifndef __G_TYPE_H__
#define __G_TYPE_H__

#include <glib.h>

typedef struct _GType {
	gsize size;
	void (*init)(void*obj);
	gpointer klass;
	gboolean *done_class_init;
	void (*class_init)(gpointer klass);
} GType;

#define G_TYPE_OBJECT 20


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

#define G_DEFINE_TYPE(ModObjName, mod_obj_name, Parent) \
	static void mod_obj_name##_class_init ( ModObjName##Class *klass ); \
	static void mod_obj_name##_init ( ModObjName *obj ); \
	static ModObjName mod_obj_name##_class; \
	static gboolean mod_obj_name##_done_class_init; \
	static gpointer mod_obj_name##_parent_class = NULL; \
	static void mod_obj_name##_class_intern_init(gpointer klass) { \
		mod_obj_name##_parent_class = (gpointer) (&((ModObjName##Class *) klass)->parent_class); \
		mod_obj_name##_class_init((ModObjName##Class *)klass); \
	} \
	GType mod_obj_name##_get_type() { \
		GType ret; \
		ret.size=sizeof(ModObjName); \
		ret.init=(void(*)(void*)) &mod_obj_name##_init; \
		ret.done_class_init=&mod_obj_name##_done_class_init; \
		ret.klass=(gpointer) &mod_obj_name##_class; \
		ret.class_init=&mod_obj_name##_class_intern_init; \
		return ret; \
	}

#endif
