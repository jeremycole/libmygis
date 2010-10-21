# The order for SUBDIRS is important, as we need to make sure
# that libmygis.* gets built in . before tests are built

SUBDIRS = extra wkb wkt e00 dbf prj shp tiger . tests doc

MAINTAINERCLEANFILES = \
  aclocal.m4 configure config.status config.log config.h \
  config.h.in Makefile.in *~

mygis_includedir      = $(includedir)/mygis
mygis_wkb_includedir   = $(mygis_includedir)/wkb
mygis_wkt_includedir   = $(mygis_includedir)/wkt
mygis_e00_includedir   = $(mygis_includedir)/e00
mygis_shp_includedir   = $(mygis_includedir)/shp
mygis_dbf_includedir   = $(mygis_includedir)/dbf
mygis_prj_includedir   = $(mygis_includedir)/prj
mygis_tiger_includedir = $(mygis_includedir)/tiger

mygis_include_HEADERS = \
  mygis.h  \
  compare.h \
  pairlist.h \
  record.h \
  fixed.h \
  projection.h \
  geometry.h \
  shapefile.h

mygis_wkb_include_HEADERS = \
  wkb/wkb.h

mygis_wkt_include_HEADERS = \
  wkt/wkt.h
  
mygis_e00_include_HEADERS = \
  e00/e00.h

mygis_shp_include_HEADERS = \
  shp/shp.h \
  shp/shx.h \
  shp/sh_header.h

mygis_dbf_include_HEADERS = \
  dbf/dbf.h
  
mygis_prj_include_HEADERS = \
  prj/prj.h

mygis_tiger_include_HEADERS = \
  tiger/tiger.h

noinst_HEADERS = \
  dbug.h \
  dbug_long.h \
  mygis_priv.h \
  fixed_priv.h \
  geometry_priv.h \
  pairlist_priv.h \
  projection_priv.h \
  record_priv.h \
  shapefile_priv.h \
  portability.h

lib_LTLIBRARIES = libmygis.la

libmygis_la_LDFLAGS = -version-info 0:0:0

libmygis_la_SOURCES = \
  dbug.c \
  mygis.c \
  portability.c \
  compare.c \
  pairlist.c \
  record.c \
  fixed.c \
  projection.c \
  geometry.c \
  shapefile.c

libmygis_la_LIBADD = \
  wkb/libwkb.la \
  wkt/libwkt.la \
  e00/libe00.la \
  dbf/libdbf.la \
  prj/libprj.la \
  shp/libshp.la \
  tiger/libtiger.la

INCLUDES = -I$(srcdir) -I$(srcdir)/..

AM_CFLAGS = @CFLAGS@
