#include <glib-object.h>

G_BEGIN_DECLS

#define HELLO_TYPE_GREETING (hello_greeting_get_type())

G_DECLARE_FINAL_TYPE (HelloGreeting, hello_greeting, HELLO, GREETING, GObject)

G_END_DECLS


struct _HelloGreeting {
	GObject parent_instance;
};


G_DEFINE_TYPE (HelloGreeting, hello_greeting, G_TYPE_OBJECT)

static void hello_greeting_class_init(HelloGreetingClass *klass) {

}

static void hello_greeting_init (HelloGreeting *self) {

}
