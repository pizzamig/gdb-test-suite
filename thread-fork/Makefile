all: thread-fork


thread-fork: thread-fork.c
	$(CC) -lpthread -O0 -g -o thread-fork thread-fork.c

clean:
	rm -f *.core thread-fork

