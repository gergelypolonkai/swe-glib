include $(top_srcdir)/swe-glib.mk

LDADD = $(top_builddir)/src/libswe-glib-2.0.la
DEFS = -DG_LOG_DOMAIN=\"SWE-GLib\"
AM_CPPFLAGS = $(GLIB_CFLAGS) $(GOBJECT_CFLAGS) $(LIBSWE_CFLAGS) -I$(top_srcdir)/src
AM_CFLAGS = -g

test_programs = gswe-timestamp-test
TESTS += $(test_programs)
