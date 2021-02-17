#ifndef __G_LIST_H
#define __G_LIST_H

#include <glib/gtypes.h>

typedef struct _GList {
	gpointer data;
	struct _GList *next;
	struct _GList *prev;
} GList;

GList *g_list_append(GList *list, gpointer data);
GList *g_list_first(GList *list);
#endif
