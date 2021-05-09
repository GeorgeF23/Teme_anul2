CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

SERVER_FILES = server.o tcp.o udp.o list.o client.o message.o
SUBSCRIBER_FILES = subscriber.o list.o client.o message.o

build: subscriber server

# make subscriber executable
subscriber: build_objects
	$(CC) $(CFLAGS) $(SUBSCRIBER_FILES) -o subscriber

# make server executable
server: build_objects
	$(CC) $(CFLAGS) $(SERVER_FILES) -o server

# build objects
build_objects: $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f server
	rm -f subscriber