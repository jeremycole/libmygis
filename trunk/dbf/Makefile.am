MAINTAINERCLEANFILES = Makefile.in *~

noinst_LTLIBRARIES = libdbf.la

libdbf_la_SOURCES = \
  dbf.c dbf_read.c dbf_scan.c dbf_misc.c dbf.h dbf_priv.h \
  ../config.h
#libdbf_la_LIBADD = ../compare.lo @LTLIBOBJS@

INCLUDES = -I$(srcdir) -I$(srcdir)/..

all: $(OBJS)
