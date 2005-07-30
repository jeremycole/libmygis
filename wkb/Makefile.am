MAINTAINERCLEANFILES = Makefile.in *~

lib_LIBRARIES = libwkb.a

libwkb_a_SOURCES = wkb.c wkb_read.c wkb.h wkb_priv.h ../geometry.h ../config.h
libwkb_a_LIBADD = $(LIBOBJS)

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
