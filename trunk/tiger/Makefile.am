MAINTAINERCLEANFILES = Makefile.in *~

noinst_LTLIBRARIES = libtiger.la

libtiger_la_SOURCES = \
  tiger.c tiger.h tiger_priv.h \
  tiger_defs.c tiger_defs.h \
  tiger_read.c \
  ../config.h

INCLUDES = -I$(srcdir) -I$(srcdir)/..

all: $(OBJS)
