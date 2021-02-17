#include <glib.h>

int main (void) {
	GString *my_string = g_string_new("Hello, World!\n");
	g_print(my_string->str);
	g_string_free(my_string, TRUE);
	return 0;
}
