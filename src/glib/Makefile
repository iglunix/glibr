.POSIX:
.SUFFIXES:
CC=c99
all: glib.so
glib.so: gstring.o gmessages.o
	$(CC) $(LDFLAGS) -shared -o glib.so gstring.o gmessages.o
gstring.o: gstring.h gtypes.h
	$(CC) -fPIC -c $(CFLAGS) -o gstring.o gstring.c
gmessages.o: gmessages.h gtypes.h
	$(CC) -fPIC -c $(CFLAGS) -o gmessages.o gmessages.c
