#ifndef __G_BOXED_H__
#define __G_BOXED_H__

#include <glib/gtypes.h>

typedef gpointer (*GBoxedCopyFunc)(gconstpointer);
typedef void (*GBoxedFreeFunc)(gpointer);

#endif
