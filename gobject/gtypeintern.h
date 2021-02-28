#include <gobject/gtype.h>
#include <gobject/gboxed.h>

void g_type_intern_register_boxed_extras(GType type, GBoxedCopyFunc cpyfunc, GBoxedFreeFunc freefunc);

GBoxedCopyFunc g_type_intern_peek_boxed_extras_cpy(GType type);

GBoxedFreeFunc g_type_intern_peek_boxed_extras_free(GType type);
