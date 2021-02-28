#include <glib/gtypes.h>
#include <stdlib.h>
#include <glib/gmem.h>

void gfree(gpointer mem) {
	free(mem);
}
