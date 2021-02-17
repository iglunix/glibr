#include <stdlib.h>
#include <glib/glist.h>

GList *g_list_append (GList *list, gpointer data) {
	GList *ret = malloc(sizeof(ret));
	ret->data = data;
	ret->prev = list;
	ret->next = 0;
	list && (list->next = ret);
	return ret;
}

GList *g_list_first(GList *list) {
	if (list->prev) {
		return g_list_first(list->prev);
	} else {
		return list;
	}
}
