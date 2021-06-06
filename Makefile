.POSIX:
.SUFFIXES:
PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
BINDIR = $(PREFIX)/bin
INCLUDEDIR = $(PREFIX)/include

all: libglib.so

samples: hello.sample hello_list.sample hello_object.sample

hello.sample: libglib.so samples/hello.c
	$(CC) -Iinclude samples/hello.c libglib.so -o hello.sample
	./hello.sample

hello_list.sample: libglib.so samples/hello_list.c
	$(CC) -Iinclude samples/hello_list.c libglib.so -o hello_list.sample
	./hello_list.sample

hello_object.sample: libglib.so samples/hello_object.c
	$(CC) -Iinclude samples/hello_object.c libglib.so -o hello_object.sample
	./hello_object.sample

clean:
	rm *.sample 2>/dev/null || exit 0
	rm *.o 2>/dev/null || exit 0
	rm *.so 2>/dev/null || exit 0

libglib.so: gstring.o gmessages.o glist.o gobject.o gtype.o gboxed.o gmem.o gthread.o gslist.o
	$(CC) $(LDFLAGS) -shared -o libglib.so gstring.o gmessages.o glist.o gslist.o gobject.o gtype.o gboxed.o gmem.o gthread.o


########
# GLIB #
########

gstring.o: include/glib/gstring.h include/glib/gtypes.h glib/gstring.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o gstring.o glib/gstring.c

gmessages.o: include/glib/gmessages.h include/glib/gtypes.h glib/gmessages.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o gmessages.o glib/gmessages.c

glist.o: include/glib/glist.h include/glib/gtypes.h glib/glist.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o glist.o glib/glist.c

gslist.o: include/glib/gslist.h include/glib/gtypes.h glib/gslist.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o gslist.o glib/gslist.c

gmem.o: include/glib/gmem.h include/glib/gtypes.h glib/gmem.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o gmem.o glib/gmem.c

gthread.o: include/glib/gthread.h include/glib/gtypes.h glib/gthread.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o gthread.o glib/gthread.c



###########
# GOBJECT #
###########

gobject.o: include/gobject/gobject.h gobject/gobject.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o gobject.o gobject/gobject.c

gtype.o: include/gobject/gtype.h gobject/gtype.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o gtype.o gobject/gtype.c

gboxed.o: include/gobject/gboxed.h gobject/gboxed.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o gboxed.o gobject/gboxed.c
#######
# GIO #
#######

install:
	mkdir -p $(DESTDIR)/$(INCLUDEDIR)/glibr $(DESTDIR)/$(LIBDIR)/pkgconfig
	cp -rf include/* $(DESTDIR)/$(INCLUDEDIR)/glibr
	cp libglib.so $(DESTDIR)/$(LIBDIR)
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libglib.so.1
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libglib-2.0.so
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libglib-2.0.so.1
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libgobject-2.0.so
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libgobject-2.0.so.1
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libgio-2.0.so
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libgio-2.0.so.1
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libgthread-2.0.so
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libgthread-2.0.so.1
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libgmodule-2.0.so
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libgmodule-2.0.so.1
	sed 's|prefix=/usr|prefix=$(PREFIX)|g' glibr.pc > $(DESTDIR)/$(LIBDIR)/pkgconfig/glibr.pc
	ln -fs glibr.pc $(DESTDIR)/$(LIBDIR)/pkgconfig/glib-2.0.pc
	ln -fs glibr.pc $(DESTDIR)/$(LIBDIR)/pkgconfig/gobject-2.0.pc
	ln -fs glibr.pc $(DESTDIR)/$(LIBDIR)/pkgconfig/gio-2.0.pc
	install -Dm755 tools/mkenums.py $(DESTDIR)/$(BINDIR)/glib-mkenums
