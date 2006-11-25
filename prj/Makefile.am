MAINTAINERCLEANFILES = Makefile.in *~

lib_LIBRARIES = libprj.a

libprj_a_SOURCES = \
  prj.c prj.h \
  prj_defs.c prj_defs.h \
  prj_yacc.y prj_yacc.h \
  prj_lex.l \
  ../config.h

libprj_a_LIBADD = \
  ../compare.o ../projection.o $(LIBOBJS)

INCLUDES = -I$(srcdir) -I..

YFLAGS = -d

all: $(OBJS)
