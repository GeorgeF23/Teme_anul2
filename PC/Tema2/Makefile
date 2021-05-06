CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

SERVER_FILES = server.o tcp.o udp.o

# make server executable
build_server: build_objects
	$(CC) $(CFLAGS) $(SERVER_FILES) -o server

# build objects
build_objects: $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f server