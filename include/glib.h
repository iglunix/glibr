#ifndef __G_LIB_H__
#define __G_LIB_H__


/*
 * If one really wants to know if they're using GLibR
 * 
 * They shouldn't need this; GLibR should be the one supporting
 * them not the otherway around
 */
#define __GLIBR__

#include <glib/gmacros.h>
#include <glib/glist.h>
#include <glib/gmessages.h>
#include <glib/gstring.h>
#include <glib/gtypes.h>
#include <glib/gtestutils.h>
#include <glib/gmem.h>
#include <glib/gthread.h>
#include <glibconfig.h>

#endif
