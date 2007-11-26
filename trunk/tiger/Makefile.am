MAINTAINERCLEANFILES = Makefile.in *~

noinst_LTLIBRARIES = libtiger.la

libtiger_la_SOURCES = \
  tiger.c tiger.h \
  tiger_defs.c tiger_defs.h \
  tiger_read.c \
  ../config.h
libtiger_la_LIBADD = ../compare.o @LTLIBOBJS@

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
