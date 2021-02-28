#ifndef __G_THREAD_H__
#define __G_THREAD_H__

#include <pthread.h>

#include <glib/gtypes.h>
#define G_THREAD_ERROR

typedef enum _GThreadError {
	G_THREAD_ERROR_AGAIN
} GThreadError;

typedef struct _GThread {
	gssize ref_count;
	pthread_t pthread;
} GThread; 

typedef pthread_mutex_t GMutex;

typedef gpointer (*GThreadFunc)(gpointer);

GThread *g_thread_new(gchar const *, GThreadFunc, gpointer);
GThread *g_thread_ref(GThread *);
void g_thread_unref(GThread *);
gpointer g_thread_join(GThread *);
void g_thread_yeild(GThread *);
void g_thread_exit(gpointer);
GThread *g_thread_self();

void g_mutex_init(GMutex *);
void g_mutex_clear(GMutex *);
void g_mutex_lock(GMutex *);
gboolean g_mutex_trylock(GMutex *);
void g_mutex_unlock(GMutex *);

#endif
