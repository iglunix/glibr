#include <stdlib.h>
#include <pthread.h>
#include <glib/gthread.h>

GThread *g_thread_new(gchar const *name, GThreadFunc func, gpointer data) {
	GThread *ret = malloc(sizeof(GThread));
	ret->ref_count = 1;
	pthread_create(&ret->pthread, NULL, func, data);
	return ret;
}

GThread *g_thread_ref(GThread *self) {
	self->ref_count++;
	return self;
}

void g_thread_unref(GThread *self) {
	self->ref_count--;
	if (!self->ref_count) {
		free(self);
	}
}

gpointer g_thread_join(GThread *self) {
	gpointer ret;
	pthread_join(self->pthread, &ret);
	return ret;
}

void g_thread_yeild(GThread *self) {
	sched_yield();
}

void g_thread_exit(gpointer ret) {
	pthread_exit(ret);
}

GThread *g_thread_self() {
	GThread *ret = malloc(sizeof(GThread));
	ret->ref_count = 1;
	ret->pthread = pthread_self();
	return ret;
}

void g_mutex_init(GMutex *self) {
	pthread_mutex_init(self, NULL);
}

void g_mutex_clear(GMutex *self) {
	pthread_mutex_destroy(self);
}

void g_mutex_lock(GMutex *self) {
	pthread_mutex_lock(self);
}

gboolean g_mutex_trylock(GMutex *self) {
	return pthread_mutex_trylock(self);
}

void g_mutex_unlock(GMutex *self) {
	pthread_mutex_unlock(self);
}
