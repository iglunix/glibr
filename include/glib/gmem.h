#ifndef __G_MEM_H__
#define __G_MEM_H__

#include <stdlib.h>
#include <glib/gtypes.h>

#define g_free(x) free((void *) x)
#define g_malloc(x) (gpointer) malloc((size_t) x)

#endif
