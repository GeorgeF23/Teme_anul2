CC = g++
CFLAGS = -Wall -Wextra -std=c++17

SRCS = $(sort $(wildcard *.cpp))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

TARGET = client

# build all targets
build: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# general rule for building a target
%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

run: build
	./$(TARGET)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
