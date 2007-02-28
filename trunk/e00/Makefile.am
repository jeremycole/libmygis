MAINTAINERCLEANFILES = Makefile.in *~

lib_LIBRARIES = libe00.a

libe00_a_SOURCES = \
  e00.c e00_read.c e00_write.c e00.h e00_priv.h \
  ../geometry.h ../config.h
libe00_a_LIBADD = $(LIBOBJS)

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
