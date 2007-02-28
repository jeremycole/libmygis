MAINTAINERCLEANFILES = Makefile.in *~

lib_LIBRARIES = libwkt.a

libwkt_a_SOURCES = wkt.c wkt_write.c wkt.h wkt_priv.h ../geometry.h ../config.h
libwkt_a_LIBADD = $(LIBOBJS)

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
