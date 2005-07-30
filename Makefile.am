SUBDIRS = wkb wkt e00 dbf shp tiger

MAINTAINERCLEANFILES = \
  aclocal.m4 configure config.status config.log config.h \
  config.h.in Makefile.in *~

include_HEADERS = \
  mygis.h portability.h dbug.h compare.h pairlist.h fixed.h geometry.h shapefile.h \
  wkb/wkb.h \
  wkt/wkt.h \
  e00/e00.h \
  shp/shp.h shp/shx.h shp/sh_header.h \
  dbf/dbf.h \
  tiger/tiger.h

lib_LIBRARIES = libmygis.a

libmygis_a_SOURCES = \
  mygis.c 

ROOT_OBJECTS = \
  portability.o \
  dbug.o \
  compare.o \
  pairlist.o \
  fixed.o \
  geometry.o \
  shapefile.o
  
libmygis_a_LIBADD = \
  $(ROOT_OBJECTS) \
  wkb/wkb.o wkb/wkb_read.o \
  wkt/wkt.o wkt/wkt_write.o \
  e00/e00.o e00/e00_read.o e00/e00_write.o \
  dbf/dbf.o dbf/dbf_read.o dbf/dbf_scan.o dbf/dbf_misc.o \
  shp/sh_header.o \
  shp/shp.o shp/shp_read.o shp/shp_write.o \
  shp/shx.o shp/shx_read.o shp/shx_write.o \
  tiger/tiger.o tiger/tiger_read.o

INCLUDES = -I$(srcdir) -I..

AM_CFLAGS = @CFLAGS@

all: $(ROOT_OBJECTS) all-recursive $(lib_LIBRARIES)
	(cd tests && make all)
	(cd tools && make all)

clean:
	(cd tools && make clean)
	(cd tests && make clean)
	rm -f $(OBJS) $(LIB)
