#ifndef __G_TYPE_H__
#define __G_TYPE_H__

#include <glib.h>

typedef gsize GType;

#define G_DECLARE_FINAL_TYPE(ModObjName, mod_obj_name, MOD, OBJ_NAME, SuperName) \
	GType mod_obj_name##_get_type(); \
	typedef struct _##ModObjName ModObjName; \
	typedef struct { \
		SuperName##Class parent_class; \
	} ModObjName##Class; \
	//TODO AUTOPTR_CHAINUP

#define G_DEFINE_TYPE(ModObjName, mod_obj_name, wtf) \
	static void mod_obj_name##_class_init ( ModObjName##Class *klass ); \
	GType mod_obj_name##_get_type() {return 0;};
#endif
