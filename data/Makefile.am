pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = swe-glib.pc $(NULL)

eu.polonkai.gergely.swe-glib.gschema.xml: gschema.template $(top_builddir)/src/gswe-types.h
	$(GLIB_MKENUMS) --comments "<!-- @comment@ -->" --template $(filter %.template,$^) $(filter-out %.template,$^) > \
	$@.tmp && mv $@.tmp $@

gsettings_SCHEMAS = eu.polonkai.gergely.swe-glib.gschema.xml

@GSETTINGS_RULES@

swephdir = $(pkgdatadir)
sweph_DATA = \
	sweph-data/seas_00.se1 \
	sweph-data/seas_06.se1 \
	sweph-data/seas_12.se1 \
	sweph-data/seas_18.se1 \
	sweph-data/seas_24.se1 \
	sweph-data/seas_30.se1 \
	sweph-data/seas_36.se1 \
	sweph-data/seas_42.se1 \
	sweph-data/seas_48.se1 \
	sweph-data/seasm06.se1 \
	sweph-data/seasm12.se1 \
	sweph-data/seasm18.se1 \
	sweph-data/seasm24.se1 \
	sweph-data/seasm30.se1 \
	sweph-data/seasm36.se1 \
	sweph-data/seasm42.se1 \
	sweph-data/seasm48.se1 \
	sweph-data/seasm54.se1 \
	sweph-data/semo_00.se1 \
	sweph-data/semo_06.se1 \
	sweph-data/semo_12.se1 \
	sweph-data/semo_18.se1 \
	sweph-data/semo_24.se1 \
	sweph-data/semo_30.se1 \
	sweph-data/semo_36.se1 \
	sweph-data/semo_42.se1 \
	sweph-data/semo_48.se1 \
	sweph-data/semom06.se1 \
	sweph-data/semom12.se1 \
	sweph-data/semom18.se1 \
	sweph-data/semom24.se1 \
	sweph-data/semom30.se1 \
	sweph-data/semom36.se1 \
	sweph-data/semom42.se1 \
	sweph-data/semom48.se1 \
	sweph-data/semom54.se1 \
	sweph-data/sepl_00.se1 \
	sweph-data/sepl_06.se1 \
	sweph-data/sepl_12.se1 \
	sweph-data/sepl_18.se1 \
	sweph-data/sepl_24.se1 \
	sweph-data/sepl_30.se1 \
	sweph-data/sepl_36.se1 \
	sweph-data/sepl_42.se1 \
	sweph-data/sepl_48.se1 \
	sweph-data/seplm06.se1 \
	sweph-data/seplm12.se1 \
	sweph-data/seplm18.se1 \
	sweph-data/seplm24.se1 \
	sweph-data/seplm30.se1 \
	sweph-data/seplm36.se1 \
	sweph-data/seplm42.se1 \
	sweph-data/seplm48.se1 \
	sweph-data/seplm54.se1 \
	sweph-data/seleapsec.txt \
	sweph-data/s136199.se1  \
	sweph-data/s136199s.se1 \
	sweph-data/se00010s.se1 \
	sweph-data/se00034s.se1 \
	sweph-data/se00157s.se1 \
	sweph-data/se07066s.se1 \
	sweph-data/se08405s.se1 \
	sweph-data/se10199s.se1 \
	sweph-data/se90377.se1  \
	sweph-data/se90377s.se1 \
	sweph-data/se90482.se1  \
	sweph-data/se90482s.se1 \
	$(NULL)

EXTRA_DIST = \
			  $(sweph_DATA) \
			  swe-glib.spec \
			  gschema.template

DISTCLEANFILES = $(gsettings_SCHEMAS)
