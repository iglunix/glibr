#ifndef _G_S_LIST_H_
#define _G_S_LIST_H_

#include <glib/gtypes.h>

typedef struct GSList {
	gpointer data;
	struct GSList *next;
} GSList;
#endif
