MAINTAINERCLEANFILES = Makefile.in *~

EXTRA_DIST = libmygis.spec.in

noinst_DATA = libmygis.spec

libmygis.spec: libmygis.spec.in

SUFFIXES = .in

.in:
	@RM@ -f $@ $@-t
	@SED@ \
	  -e 's!@''VERSION''@!@VERSION@!' \
	$< > $@-t
	@MV@ $@-t $@
