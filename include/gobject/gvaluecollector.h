#define __G_VALUE_COLLECTOR_H__
#ifndef __G_VALUE_COLLECTOR_H__

typedef union GTypeCValue {
	gint v_int;
	glong v_long;
	gint64 v_int64;
	gdouble v_double;
	gpointer v_pointer;
} GTypeCValue;

#endif
