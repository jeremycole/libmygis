MAINTAINERCLEANFILES = Makefile.in *~

noinst_DATA = variables.texi libmygis.html
CLEANFILES = $(noinst_DATA)
EXTRA_DIST = variables.texi.in libmygis.texi

variables.texi: variables.texi.in ../configure.in
	@RM@ -f $@ $@-t
	@SED@ \
	  -e 's!@''VERSION''@!@VERSION@!' \
	$< > $@-t
	@MV@ $@-t $@

.texi.html: $< variables.texi.in variables.texi
	texi2html $<

