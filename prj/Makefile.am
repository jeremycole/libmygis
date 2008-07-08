MAINTAINERCLEANFILES = Makefile.in *~

noinst_LTLIBRARIES = libprj.la

libprj_la_SOURCES = \
  prj_yacc.y prj_yacc.h \
  prj_lex.l \
  prj.c prj.h \
  prj_defs.c prj_defs.h \
  ../config.h

#libprj_la_LIBADD = \
#  ../compare.lo ../projection.lo @LTLIBOBJS@

INCLUDES = -I$(srcdir) -I$(srcdir)/..

AM_YFLAGS = -d

all: $(OBJS)
