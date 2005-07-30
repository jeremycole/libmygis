MAINTAINERCLEANFILES = Makefile.in *~

lib_LIBRARIES = libtiger.a

libtiger_a_SOURCES = \
  tiger.c tiger_read.c tiger.h \
  ../config.h
libtiger_a_LIBADD = ../compare.o $(LIBOBJS)

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
