MAINTAINERCLEANFILES = Makefile.in *~

lib_LIBRARIES = libshp.a

libshp_a_SOURCES = \
  sh_header.c sh_header.h \
  shp.c shp_read.c shp_write.c shp.h shp_priv.h \
  shx.c shx_read.c shx_write.c shx.h shx_priv.h \
  ../geometry.h ../config.h
libshp_a_LIBADD = $(LIBOBJS)

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
