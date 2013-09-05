AM_CPPFLAGS = -DG_LOG_DOMAIN=\"SWE-GLib\" -DLOCALEDIR=\"$(localedir)\" -D__SWE_GLIB_BUILDING__

lib_LTLIBRARIES = libswe-glib-0.1.la

INST_H_SRC_FILES = \
	swe-glib.h     \
	gswe-types.h   \
	gswe-moment.h  \
	gswe-timestamp.h

INST_H_BUILT_FILES = \
	enumtypes.h

libswe_glib_sources = swe-glib.c gswe-moment.c gswe-timestamp.c enumtypes.c
gswe_headers = gswe-timestamp.h gswe-types.h

libswe_glib_0_1_la_SOURCES = $(libswe_glib_sources)
libswe_glib_0_1_la_CFLAGS = $(GLIB_CFLAGS) $(GOBJECT_CFLAGS) -Wall
libswe_glib_0_1_la_LIBADD = $(GLIB_LIBS) $(GOBJECT_LIBS) $(LIBSWE_LIBS)

BUILT_SOURCES = enumtypes.c enumtypes.h

CLEANFILES = $(BUILT_SOURCES)

EXTRA_DIST = enumtypes.h.template enumtypes.c.template

enumtypes.h: $(gswe_headers) enumtypes.h.template
	$(GLIB_MKENUMS) --template $(filter %.template,$^) $(filter-out %.template,$^) > \
	enumtypes.h.tmp && mv enumtypes.h.tmp enumtypes.h

enumtypes.c: $(gswe_headers) enumtypes.h enumtypes.c.template
	$(GLIB_MKENUMS) --template $(filter %.template,$^) $(filter-out %.template,$^) > \
	enumtypes.c.tmp && mv enumtypes.c.tmp enumtypes.c

if HAVE_INTROSPECTION

include $(INTROSPECTION_MAKEFILE)
SweGlib-$(SWE_GLIB_API_VERSION).gir: libswe-glib-0.1.la
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_FILES = $(INST_H_SRC_FILES) $(INST_H_BUILT_FILES) $(filter %.c,$(libswe_glib_0_1_la_SOURCES))
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_LIBS = libswe-glib-0.1.la
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_SCANNERFLAGS = --identifier-prefix=Gswe --symbol-prefix=gswe --warn-all
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_INCLUDES = GLib-2.0 GObject-2.0
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_CFLAGS = -D__SWE_GLIB_BUILDING__ -I$(top_srcdir) -I$(srcdir) -I$(builddir)
SweGlib_@SWE_GLIB_API_VERSION_U@_gir_EXPORT_PACKAGES = swe-glib
INTROSPECTION_GIRS = SweGlib-$(SWE_GLIB_API_VERSION).gir

girdir = $(datadir)/gir-1.0
gir_DATA = SweGlib-$(SWE_GLIB_API_VERSION).gir

typelibsdir = $(libdir)/girepository-1.0
typelibs_DATA = SweGlib-$(SWE_GLIB_API_VERSION).typelib

CLEANFILES += $(gir_DATA) $(typelibs_DATA)

endif
