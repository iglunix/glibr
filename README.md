# GLibR
A reimplementation of GLib under a permissive license.

## Why
Because lots of things need it and Iglunix isn't allowed to use
any GNU software.

## Opinions
In my opinion, gobject is bloated and a much simpler object system
could be implemented. The following is a much simpler object library
in a single header file.

```c
#include <stddef.h>
#include <stdlib.h>

/*
 * Object namespace info
 */

#define OBJECT_TYPE Object
#define OBJECT_PREFIX object
#define OBJECT_SUPER Object

/*
 * Base Object: everything must inherit from this eventually
 */
typedef struct Object {
	size_t refc;
} Object;

/* 
 * Base Object constructor: all constructors must call their supers constructor
 */
void object_new(Object *object) {
	object->refc = 1;
}

/*
 * Base Object destructor: all destructors must call this
 * returns: reference count
 * 
 * If on heap, one should do `object_del(obj)||free(obj)`
 */
size_t object_del(Object *object) {
	object->refc-=1;
	return object->refc;
}

/*
 * Create a new reference to an object
 */
Object *object_new_ref(Object *object) {
	object->refc+=1;
	return object;
}

#define __UCAT(a,b) a##_##b
#define ___UCAT(a,b) __UCAT(a,b)

#define NEW_REF(OBJ_NAME,var_name) (OBJ_NAME##_TYPE *) object_new_ref((Object *) var_name)

#define HEAP_DEL(OBJ_NAME,var_name) if (!___UCAT(OBJ_NAME##_PREFIX, del)(var_name)) free(var_name);

#define BEGIN_CLASS_DECL

/*
 * The following must be defined to outline information about the type
 *
 *	#define OBJ_NAME##_TYPE ObjName
 *	#define OBJ_NAME##_PREFIX obj_name
 *	#define OBJ_NAME##_SUPER SUPER##_TYPE
 * 	#define OBJ_NAME##_SUPER_PREFIX SUPER##_PREFIX
 */

#define END_CLASS_DECL(OBJ_NAME) \
	struct OBJ_NAME##_TYPE; \
	typedef struct OBJ_NAME##_TYPE OBJ_NAME##_TYPE;

#define BEGIN_CLASS(OBJ_NAME) \
	struct OBJ_NAME##_TYPE { \
		OBJ_NAME##_SUPER super;

#define END_CLASS };


#define METHOD_DECL(OBJ_NAME,ret_type,method_name, ...) \
	ret_type ___UCAT(OBJ_NAME##_PREFIX, method_name) (OBJ_NAME##_TYPE *self, ##__VA_ARGS__);

#define BEGIN_METHOD(OBJ_NAME,ret_type,method_name, ...) \
	ret_type ___UCAT(OBJ_NAME##_PREFIX, method_name) (OBJ_NAME##_TYPE *self, ##__VA_ARGS__) { \
		OBJ_NAME##_SUPER *super = (OBJ_NAME##_SUPER *)self;

#define END_METHOD }
	                                                               
#define BEGIN_DEL(OBJ_NAME) \
	size_t ___UCAT(OBJ_NAME##_PREFIX, del)(OBJ_NAME##_TYPE *self) { \
		size_t __ref_count = ___UCAT(OBJ_NAME##_SUPER_PREFIX, del)((OBJ_NAME##_SUPER *) self); \
		if (!__ref_count) {

#define END_DEL }; return __ref_count; }

#define MALLOC_OBJECT(OBJ_NAME,var_name) OBJ_NAME##_TYPE *var_name = malloc(sizeof(OBJ_NAME##_TYPE));
```
