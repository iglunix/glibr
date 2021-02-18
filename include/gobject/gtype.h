#ifndef __G_TYPE_H__
#define __G_TYPE_H__

#include <glib.h>

typedef struct _GType {
	gsize size;
	void (*init)(void*obj);
	gboolean *done_class_init;
	void (*class_init)(void*klass);
} GType;

#define G_DECLARE_FINAL_TYPE(ModObjName, mod_obj_name, MOD, OBJ_NAME, SuperName) \
	GType mod_obj_name##_get_type(); \
	typedef struct _##ModObjName ModObjName; \
	typedef struct { \
		SuperName##Class parent_class; \
	} ModObjName##Class;
	//TODO AUTOPTR_CHAINUP

#define G_DEFINE_TYPE(ModObjName, mod_obj_name, wtf) \
	static void mod_obj_name##_class_init ( ModObjName##Class *klass ); \
	static void mod_obj_name##_init ( ModObjName *obj ); \
	static gboolean mod_obj_name##_done_class_init = FALSE; \
	GType mod_obj_name##_get_type() { \
		GType ret; \
		ret.size=sizeof(ModObjName); \
		ret.init=(void(*)(void*)) &mod_obj_name##_init; \
		ret.done_class_init=&mod_obj_name##_done_class_init; \
		ret.class_init=(void(*)(void*)) &mod_obj_name##_class_init; \
		return ret; \
	}

#endif
