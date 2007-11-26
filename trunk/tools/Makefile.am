MAINTAINERCLEANFILES = Makefile.in *~

bin_PROGRAMS = \
	mysqlgisimport

mysqlgisimport_SOURCES = mysqlgisimport.c
mysqlgisimport_LDADD = ../libmygis.la

INCLUDES = -I$(srcdir) -I..

all: $(OBJS)
