CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -g
LDFLAGS = -lm

SRCS = $(sort $(wildcard *.cpp))
TARGETS = $(patsubst %.cpp,%,$(SRCS))

# build all targets
build: $(TARGETS)

# general rule for building a target
%: %.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

run-p1:      # nume necesar
	./crypto

run-p2:      # nume necesar
	./stocks

run-p3:      # nume necesar
	./valley

run-p4:      # nume necesar
	./ridge

clean:		 # nume necesar
	rm -f crypto
	rm -f stocks
	rm -f valley
	rm -f ridge