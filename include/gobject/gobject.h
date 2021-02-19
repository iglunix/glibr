#ifndef __G_OBJECT_H__
#define __G_OBJECT_H__

#include <gobject/gtype.h>
#include <gobject/gvalue.h>

typedef struct _GObject {
	volatile unsigned int ref_count;
} GObject;

typedef struct _GObjectConstructParam {
	GValue *value;
} GObjectConstructParam;

typedef struct _GObjectClass {
	/*
         * Function for allocating a GObject
         */
	gpointer (*constructor)(GType, guint, GObjectConstructParam *);
	/*
         * Function for initialising a GObject
         */
	void (*init)(gpointer);
} GObjectClass;



/*
 * TODO
 */
#define G_OBJECT(object) object
#define G_OBJECT_CLASS(class) G_TYPE_CHECK_CLASS_CAST(class, G_TYPE_OBJECT, GObjectClass)

GObject *g_object_new(GType type, gchar const *, ...);

gpointer g_object_ref(gpointer object);
void g_object_unref(gpointer object);

#endif
