.POSIX:

all: glib

glib:
	$(MAKE) -C src/glib

test:
	$(MAKE) -C samples

clean:
	$(MAKE) -C samples clean
	$(MAKE) -C src/glib clean
