MAINTAINERCLEANFILES = Makefile.in *~

lib_LIBRARIES = libdbf.a

libdbf_a_SOURCES = \
  dbf.c dbf_read.c dbf_scan.c dbf_misc.c dbf.h dbf_priv.h \
  ../config.h
libdbf_a_LIBADD = ../compare.o $(LIBOBJS)

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
