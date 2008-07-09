MAINTAINERCLEANFILES = Makefile.in *~

noinst_LTLIBRARIES = libwkb.la

libwkb_la_SOURCES = wkb.c wkb_read.c wkb_write.c wkb_misc.c wkb.h wkb_priv.h ../geometry.h ../config.h

INCLUDES = -I$(srcdir) -I$(srcdir)/..

all: $(OBJS)
