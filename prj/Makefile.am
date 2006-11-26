MAINTAINERCLEANFILES = Makefile.in *~

lib_LIBRARIES = libprj.a

libprj_a_SOURCES = \
  prj_yacc.y prj_yacc.h \
  prj_lex.l \
  prj.c prj.h \
  prj_defs.c prj_defs.h \
  ../config.h

libprj_a_LIBADD = \
  ../compare.o ../projection.o $(LIBOBJS)

INCLUDES = -I$(srcdir) -I..

YFLAGS = -d

all: $(OBJS)
