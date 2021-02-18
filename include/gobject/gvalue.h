#ifndef _G_VALUE_H_
#define _G_VALUE_H_

#include <glib/gtypes.h>

typedef struct _GValue {
	GType g_type;
	union {
		gint v_int;
		guint v_uint;
		glong v_long;
		gulong v_ulong;
		gint64 v_int64;
		guint64 v_uint64;
		gfloat v_float;
		gdouble v_double;
		gpointer v_pointer;
	} data[2];
} GValue;

#endif
