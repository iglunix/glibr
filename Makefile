.POSIX:
.SUFFIXES:
PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
INCLUDEDIR = $(PREFIX)/include

all: libglib.so

samples: hello.sample hello_list.sample

hello.sample: libglib.so samples/hello.c
	$(CC) -Iinclude samples/hello.c libglib.so -o hello.sample
	./hello.sample

hello_list.sample: libglib.so samples/hello_list.c
	$(CC) -Iinclude samples/hello_list.c libglib.so -o hello_list.sample
	./hello_list.sample

clean:
	rm *.sample 2>/dev/null || exit 0
	rm *.o 2>/dev/null || exit 0
	rm *.so 2>/dev/null || exit 0

libglib.so: gstring.o gmessages.o glist.o
	$(CC) $(LDFLAGS) -shared -o libglib.so gstring.o gmessages.o glist.o

gstring.o: include/glib/gstring.h include/glib/gtypes.h glib/gstring.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o gstring.o glib/gstring.c

gmessages.o: include/glib/gmessages.h include/glib/gtypes.h glib/gmessages.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o gmessages.o glib/gmessages.c

glist.o: include/glib/glist.h include/glib/gtypes.h glib/glist.c
	$(CC) -Iinclude/ -fPIC -c $(CFLAGS) -o glist.o glib/glist.c

install:
	mkdir -p $(DESTDIR)/$(INCLUDEDIR) $(DESTDIR)/$(LIBDIR)
	cp -rf include/* $(DESTDIR)/$(INCLUDEDIR)
	cp libglib.so $(DESTDIR)/$(LIBDIR)
	ln -fs libglib.so $(DESTDIR)/$(LIBDIR)/libglib.so.1
