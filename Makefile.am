SUBDIRS = wkb wkt e00 dbf prj shp tiger

MAINTAINERCLEANFILES = \
  aclocal.m4 configure config.status config.log config.h \
  config.h.in Makefile.in *~

mygisincludedir = $(includedir)/mygis
mygiswkbincludedir = $(mygisincludedir)/wkb
mygiswktincludedir = $(mygisincludedir)/wkt
mygise00includedir = $(mygisincludedir)/e00
mygisshpincludedir = $(mygisincludedir)/shp
mygisdbfincludedir = $(mygisincludedir)/dbf
mygisprjincludedir = $(mygisincludedir)/prj
mygistigerincludedir = $(mygisincludedir)/tiger

mygisinclude_HEADERS = \
  mygis.h  \
  dbug.h \
  compare.h \
  pairlist.h \
  record.h \
  fixed.h \
  projection.h \
  geometry.h \
  shapefile.h

mygiswkbinclude_HEADERS = \
  wkb/wkb.h

mygiswktinclude_HEADERS = \
  wkt/wkt.h
  
mygise00include_HEADERS = \
  e00/e00.h

mygisshpinclude_HEADERS = \
  shp/shp.h \
  shp/shx.h \
  shp/sh_header.h

mygisdbfinclude_HEADERS = \
  dbf/dbf.h
  
mygisprjinclude_HEADERS = \
  prj/prj.h

mygistigerinclude_HEADERS = \
  tiger/tiger.h

noinst_HEADERS = \
  portability.h

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

install: all install-recursive
	(cd tests && make install)
	(cd tools && make install)
