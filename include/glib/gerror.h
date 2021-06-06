#ifndef _G_ERROR_H_
#define _G_ERROR_H_

#include <glib/gtypes.h>

typedef struct _GError {
	gchar *message;
} GError;

#endif
