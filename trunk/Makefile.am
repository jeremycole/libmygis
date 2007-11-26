SUBDIRS = wkb wkt e00 dbf prj shp tiger

MAINTAINERCLEANFILES = \
  aclocal.m4 configure config.status config.log config.h \
  config.h.in Makefile.in *~

include_HEADERS = \
  mygis.h portability.h dbug.h \
  compare.h pairlist.h \
  record.h fixed.h \
  projection.h \
  geometry.h \
  shapefile.h \
  wkb/wkb.h \
  wkt/wkt.h \
  e00/e00.h \
  shp/shp.h shp/shx.h shp/sh_header.h \
  dbf/dbf.h \
  prj/prj.h \
  tiger/tiger.h

lib_LTLIBRARIES = libmygis.la

libmygis_la_SOURCES = \
  mygis.c 

ROOT_OBJECTS = \
  portability.lo \
  dbug.lo \
  compare.lo \
  pairlist.lo \
  record.lo \
  fixed.lo \
  projection.lo \
  geometry.lo \
  shapefile.lo

libmygis_la_LIBADD = \
  $(ROOT_OBJECTS) \
  wkb/libwkb.la \
  wkt/libwkt.la \
  e00/libe00.la \
  dbf/libdbf.la \
  prj/libprj.la \
  shp/libshp.la \
  tiger/libtiger.la

INCLUDES = -I$(srcdir) -I..

AM_CFLAGS = @CFLAGS@

all: $(ROOT_OBJECTS) all-recursive $(lib_LIBRARIES)
	(cd tests && make all)
	(cd tools && make all)
