MAINTAINERCLEANFILES = Makefile.in *~

EXTRA_DIST = libmygis.spec.sh

noinst_DATA = libmygis-@VERSION@.spec

libmygis.spec: libmygis.spec.sh

libmygis-@VERSION@.spec: libmygis.spec
			rm -f $@
			cp $< $@

SUFFIXES = .sh

.sh:
	@RM@ -f $@ $@-t
	@SED@ \
	  -e 's!@''VERSION''@!@VERSION@!' \
	$< > $@-t
	@MV@ $@-t $@

all: $(OBJS)
