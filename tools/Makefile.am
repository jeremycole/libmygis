MAINTAINERCLEANFILES = Makefile.in *~

bin_PROGRAMS = \
	mysqlgisimport

mysqlgisimport_SOURCES = mysqlgisimport.c
mysqlgisimport_LDADD = $(LIBOBJS) ../libmygis.a -L/usr/local/lib -lproj

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
