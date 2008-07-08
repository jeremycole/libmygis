MAINTAINERCLEANFILES = Makefile.in *~

noinst_LTLIBRARIES = libwkt.la

libwkt_la_SOURCES = wkt.c wkt_write.c wkt.h wkt_priv.h \
  ../geometry.h ../config.h
libwkt_la_LIBADD = @LTLIBOBJS@

INCLUDES = -I$(srcdir) -I$(srcdir)/..

all: $(OBJS)
