.POSIX:
.SUFFIXES:

all: hello hello_list

hello: hello.c
	$(CC) -I../include hello.c ../src/glib/glib.so -o hello.sample
	./hello.sample

hello_list: hello_list.c
	$(CC) -I../include hello_list.c ../src/glib/glib.so -o hello_list.sample
	./hello_list.sample

clean:
	rm *.sample 2>/dev/null || exit 0
