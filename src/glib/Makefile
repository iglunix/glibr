.POSIX:
.SUFFIXES:
CC=c99
all: glib.so
glib.so: gstring.o
	$(CC) $(LDFLAGS) -shared -o glib.so gstring.o
gstring.o: gtypes.h
	$(CC) -fPIC -c $(CFLAGS) -o gstring.o gstring.c
