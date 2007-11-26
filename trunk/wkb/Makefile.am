MAINTAINERCLEANFILES = Makefile.in *~

noinst_LTLIBRARIES = libwkb.la

libwkb_la_SOURCES = wkb.c wkb_read.c wkb_write.c wkb_misc.c wkb.h wkb_priv.h ../geometry.h ../config.h
libwkb_la_LIBADD = @LTLIBOBJS@

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
