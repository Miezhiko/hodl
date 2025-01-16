CFLAGS=-O3 -ffast-math -Wall
CSRC=hodl.c
INSTALL   ?= install
MKDIR     ?= $(INSTALL) -d
BINDIR    ?= $(PREFIX)/bin
DESTDIR   ?=

all: hodl

rebuild: clean all

hodl: $(CSRC)
	$(CC) $(CFLAGS) -I . $(CSRC) -o hodl

install: hodl
	$(MKDIR) $(DESTDIR)$(BINDIR)
	$(INSTALL) hodl $(DESTDIR)$(BINDIR)

clean:
	rm -f hodl
	find . -name '*~' -delete;
	find . -name '#*#' -delete;
