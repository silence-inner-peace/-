TARGETS = basic cuda ib cudabw

# make sure PKG_CONFIG_PATH contains the path to $prefix/lib/pkgconfig
CFLAGS=$(shell pkg-config --cflags hwloc)
LDFLAGS=$(shell pkg-config --libs hwloc)

all: $(TARGETS)

basic: basic.c
	$(CC) $(CFLAGS) -Wall $< $(LDFLAGS) -o $@

cuda: cuda.c
	$(CC) $(CFLAGS) -Wall $< $(LDFLAGS) -o $@ -lcudart

ib: ib.c
	$(CC) $(CFLAGS) -Wall $< $(LDFLAGS) -o $@ -libverbs

cudabw: cudabw.c
	$(CC) $(CFLAGS) -std=c99 -Wall $< $(LDFLAGS) -o $@ -lcudart

clean:
	$(RM) $(TARGETS)
