MAINTAINERCLEANFILES = Makefile.in *~

lib_LIBRARIES = libtiger.a

libtiger_a_SOURCES = \
  tiger.c tiger.h \
  tiger_defs.c tiger_defs.h \
  tiger_read.c \
  ../config.h
libtiger_a_LIBADD = ../compare.o $(LIBOBJS)

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
