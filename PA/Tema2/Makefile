# Preluat din laborator
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -ggdb
LDFLAGS = -lm

SRCS = $(sort $(wildcard *.cpp))
TARGETS = $(patsubst %.cpp,%,$(SRCS))

# build all targets
build: $(TARGETS)

# general rule for building a target
%: %.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

run-p1:      # nume necesar
	./poduri

run-p2:      # nume necesar
	./adrese

run-p3:      # nume necesar
	./lego

run-p4:      # nume necesar

clean:		 # nume necesar
	rm -f poduri
	rm -f adrese
	rm -f lego