CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

SERVER_FILES = server.o tcp.o udp.o
SUBSCRIBER_FILES = subscriber.o list.o

build: build_server build_subscriber

# make subscriber executable
build_subscriber: build_objects
	$(CC) $(CFLAGS) $(SUBSCRIBER_FILES) -o subscriber

# make server executable
build_server: build_objects
	$(CC) $(CFLAGS) $(SERVER_FILES) -o server

# build objects
build_objects: $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f server
	rm -f subscriber