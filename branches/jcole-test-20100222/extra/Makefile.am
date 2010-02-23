MAINTAINERCLEANFILES = Makefile.in *~

noinst_DATA = libmygis.spec
CLEANFILES = $(noinst_DATA)
EXTRA_DIST = libmygis.spec.in

libmygis.spec: libmygis.spec.in ../configure.in

SUFFIXES = .in

.in:
	@RM@ -f $@ $@-t
	@SED@ \
	  -e 's!@''VERSION''@!@VERSION@!' \
	$< > $@-t
	@MV@ $@-t $@
