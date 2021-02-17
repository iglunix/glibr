#ifndef __G_OBJECT_H__
#define __G_OBJECT_H__

#include <gobject/gtype.h>

typedef struct _GObject {
	volatile unsigned int ref_count;
} GObject;

typedef struct _GObjectClass {
	GObject *(*constructor)(/* TODO */);
} GObjectClass;

GObject *g_object_new(GType type, gchar const *, ...);

#endif
