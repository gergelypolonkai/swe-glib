## Process this file with automake to produce Makefile.in

include $(top_srcdir)/swe-glib.mk

AM_CPPFLAGS = -DG_LOG_DOMAIN=\"SWE-GLib\" -DLOCALEDIR=\"$(localedir)\" -D__SWE_GLIB_BUILDING__ -DPKGDATADIR=\"$(pkgdatadir)\"

lib_LTLIBRARIES = libswe-glib-2.0.la

INST_H_SRC_FILES = \
	swe-glib.h                 \
	gswe-types.h               \
	gswe-moon-phase-data.h     \
	gswe-sign-info.h           \
	gswe-planet-info.h         \
	gswe-planet-data.h         \
	gswe-aspect-info.h         \
	gswe-aspect-data.h         \
	gswe-antiscion-axis-info.h \
	gswe-antiscion-data.h      \
	gswe-house-system-info.h   \
	gswe-house-data.h          \
	gswe-moment.h              \
	gswe-timestamp.h           \
	$(NULL)

INST_H_BUILT_FILES = \
	gswe-enumtypes.h \
	gswe-version.h   \
	$(NULL)

PRIV_H_SRC_FILES = \
	swe-glib-private.h                 \
	gswe-moon-phase-data-private.h     \
	gswe-sign-info-private.h           \
	gswe-planet-info-private.h         \
	gswe-planet-data-private.h         \
	gswe-aspect-info-private.h         \
	gswe-aspect-data-private.h         \
	gswe-antiscion-axis-info-private.h \
	gswe-antiscion-data-private.h      \
	gswe-house-system-info-private.h   \
	gswe-house-data-private.h          \
	$(NULL)

gswe_enum_headers = gswe-timestamp.h gswe-types.h

libswe_glib_2_0_la_SOURCES = \
	swe-glib.c                 \
	gswe-types.c               \
	gswe-moon-phase-data.c     \
	gswe-sign-info.c           \
	gswe-planet-info.c         \
	gswe-planet-data.c         \
	gswe-aspect-info.c         \
	gswe-aspect-data.c         \
	gswe-antiscion-axis-info.c \
	gswe-antiscion-data.c      \
	gswe-house-system-info.c   \
	gswe-house-data.c          \
	gswe-moment.c              \
	gswe-timestamp.c           \
	gswe-enumtypes.c           \
	gswe-version.c             \
	$(NULL)

libswe_glib_2_0_la_CFLAGS = $(GLIB_CFLAGS) $(GOBJECT_CFLAGS) -Wall
libswe_glib_2_0_la_LIBADD = $(GLIB_LIBS) $(GOBJECT_LIBS) $(LIBSWE_LIBS)
libswe_glib_2_0_la_DEPENDENCIES = \
	$(NULL)

BUILT_SOURCES = gswe-enumtypes.c gswe-enumtypes.h

CLEANFILES = $(BUILT_SOURCES)

EXTRA_DIST = gswe-enumtypes.h.template gswe-enumtypes.c.template $(PRIV_H_SRC_FILES) $(INST_H_SRC_FILES)

gswe-enumtypes.h: $(gswe_enum_headers) gswe-enumtypes.h.template
	$(GLIB_MKENUMS) --template $(filter %.template,$^) $(filter-out %.template,$^) > \
	gswe-enumtypes.h.tmp && mv gswe-enumtypes.h.tmp gswe-enumtypes.h

gswe-enumtypes.c: $(gswe_enum_headers) gswe-enumtypes.h gswe-enumtypes.c.template
	$(GLIB_MKENUMS) --template $(filter %.template,$^) $(filter-out %.template,$^) > \
	gswe-enumtypes.c.tmp && mv gswe-enumtypes.c.tmp gswe-enumtypes.c

SweGlib-2.0.vapi: SweGlib-$(SWE_GLIB_API_VERSION).gir
	$(AM_V_GEN)$(VAPIGEN) --library=SweGlib-2.0 SweGlib-2.0.gir

if HAVE_INTROSPECTION

include $(INTROSPECTION_MAKEFILE)
SweGlib-$(SWE_GLIB_API_VERSION).gir: libswe-glib-2.0.la
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_FILES = $(INST_H_SRC_FILES) $(INST_H_BUILT_FILES) $(filter %.c,$(libswe_glib_2_0_la_SOURCES))
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_LIBS = libswe-glib-2.0.la
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_SCANNERFLAGS = --identifier-prefix=Gswe --symbol-prefix=gswe --warn-all
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_INCLUDES = GLib-2.0 GObject-2.0
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_CFLAGS = -D__SWE_GLIB_BUILDING__ -I$(top_srcdir) -I$(srcdir) -I$(builddir)
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_EXPORT_PACKAGES = swe-glib
INTROSPECTION_GIRS = SweGlib-$(SWE_GLIB_API_VERSION).gir

girdir = $(datadir)/gir-1.0
gir_DATA = SweGlib-$(SWE_GLIB_API_VERSION).gir

typelibsdir = $(libdir)/girepository-1.0
typelibs_DATA = SweGlib-$(SWE_GLIB_API_VERSION).typelib

headerdir = $(includedir)/swe-glib
header_DATA = \
	$(INST_H_SRC_FILES)   \
	$(INST_H_BUILT_FILES) \
	$(NULL)

CLEANFILES += $(gir_DATA) $(typelibs_DATA)

if HAVE_VAPIGEN
vapidir = $(datadir)/vala/vapi
vapi_DATA = SweGlib-$(SWE_GLIB_API_VERSION).vapi
endif

endif
