PROJECT=router
SOURCES=router.c queue.c list.c skel.c parser.c arp.c
LIBRARY=nope
INCPATHS=include
LIBPATHS=.
LDFLAGS=
CFLAGS=-c -Wall
CC=gcc

# Automatic generation of some important lists
OBJECTS=$(SOURCES:.c=.o)
INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
LIBFLAGS=$(foreach TMP,$(LIBPATHS),-L$(TMP))

# Set up the output file names for the different output types
BINARY=$(PROJECT)

all: $(SOURCES) $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(LIBFLAGS) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(INCFLAGS) $(CFLAGS) -fPIC $< -o $@

distclean: clean
	rm -f $(BINARY)

clean:
	rm -f $(OBJECTS)
	rm -f router

run0:
	./router rtable0.txt rr-0-1 r-0 r-1

run1:
	./router rtable1.txt rr-0-1 r-0 r-1

clean_checker:
	rm -rf hosts_output
	rm -f router_0_*
	rm -f router_1_*
	rm -f router0
	rm -f router1
	rm -f rtable.txt

