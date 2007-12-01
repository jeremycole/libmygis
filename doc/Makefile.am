MAINTAINERCLEANFILES = Makefile.in *~

SUFFIXES = .in

noinst_DATA = variables.texi libmygis.html

variables.texi: variables.texi.in
	@RM@ -f $@ $@-t
	@SED@ \
	  -e 's!@''VERSION''@!@VERSION@!' \
	$< > $@-t
	@MV@ $@-t $@

.texi.html: $< variables.texi.in variables.texi ../configure.in
	texi2html $<

.in:
	@RM@ -f $@ $@-t
	@SED@ \
	  -e 's!@''VERSION''@!@VERSION@!' \
	$< > $@-t
	@MV@ $@-t $@
