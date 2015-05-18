
CFLAGS=-lpthread -g $(DEBUGFLAGS)
RTFLAGS=-lrt

SOURCES=	sigev_thread.c
PROGRAMS=$(SOURCES:.c=)

all:	sigev_thread

sigev_thread:
	${CC} ${CFLAGS} ${RTFLAGS} ${LDFLAGS} -o $@ sigev_thread.c
clean:
	@rm -rf $(PROGRAMS) *.o

recompile:	clean all
