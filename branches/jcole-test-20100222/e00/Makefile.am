MAINTAINERCLEANFILES = Makefile.in *~

noinst_LTLIBRARIES = libe00.la

libe00_la_SOURCES = \
  e00.c e00_read.c e00_write.c e00.h e00_priv.h \
  ../geometry.h ../config.h

INCLUDES = -I$(srcdir) -I$(srcdir)/..

all: $(OBJS)
