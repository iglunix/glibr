.POSIX:

all: glib

glib:
	make -C src/glib

test:
	make -C samples

clean:
	make -C samples clean
	make -C src/glib clean
