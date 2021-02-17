.POSIX:
.SUFFIXES:
CC=c99
all: libglib.so
libglib.so: gstring.o gmessages.o glist.o
	$(CC) $(LDFLAGS) -shared -o glib.so gstring.o gmessages.o glist.o
gstring.o: ../../include/glib/gstring.h ../../include/glib/gtypes.h
	$(CC) -I../../include/ -fPIC -c $(CFLAGS) -o gstring.o gstring.c
gmessages.o: ../../include/glib/gmessages.h ../../include/glib/gtypes.h
	$(CC) -I../../include/ -fPIC -c $(CFLAGS) -o gmessages.o gmessages.c
glist.o: ../../include/glib/glist.h ../../include/glib/gtypes.h
	$(CC) -I../../include/ -fPIC -c $(CFLAGS) -o glist.o glist.c
clean:
	rm *.o 2>/dev/null || exit 0
	rm *.so 2>/dev/null || exit 0

install:
	cp 
