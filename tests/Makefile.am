MAINTAINERCLEANFILES = Makefile.in *~

noinst_PROGRAMS = \
	test_swap \
	test_pairlist \
	test_projection \
	test_fixed test_fixed_usps \
	test_wkb \
	test_e00 \
	test_shp test_shx \
	test_dbf test_dbf_scan \
	test_prj \
	test_shapefile test_shapefile_scan test_shapefile_projection \
	test_tiger

test_swap_SOURCES = test_swap.c

test_pairlist_SOURCES = test_pairlist.c
test_pairlist_LDADD = ../libmygis.la

test_projection_SOURCES = test_projection.c
test_projection_LDADD = ../libmygis.la

test_fixed_SOURCES = test_fixed.c
test_fixed_LDADD = ../libmygis.la

test_fixed_usps_SOURCES = test_fixed_usps.c
test_fixed_usps_LDADD = ../libmygis.la

test_wkb_SOURCES = test_wkb.c
test_wkb_LDADD = ../libmygis.la

test_e00_SOURCES = test_e00.c
test_e00_LDADD = ../libmygis.la

test_shp_SOURCES = test_shp.c
test_shp_LDADD = ../libmygis.la

test_shx_SOURCES = test_shx.c
test_shx_LDADD = ../libmygis.la

test_dbf_SOURCES = test_dbf.c
test_dbf_LDADD = ../libmygis.la

test_dbf_scan_SOURCES = test_dbf_scan.c
test_dbf_scan_LDADD = ../libmygis.la

test_prj_SOURCES = test_prj.c
test_prj_LDADD = ../libmygis.la

test_shapefile_SOURCES = test_shapefile.c
test_shapefile_LDADD = ../libmygis.la

test_shapefile_scan_SOURCES = test_shapefile_scan.c
test_shapefile_scan_LDADD = ../libmygis.la

test_shapefile_projection_SOURCES = test_shapefile_projection.c
test_shapefile_projection_LDADD = ../libmygis.la

test_tiger_SOURCES = test_tiger.c
test_tiger_LDADD = ../libmygis.la

INCLUDES = -I$(srcdir) -I$(srcdir)/..

all: $(OBJS)
