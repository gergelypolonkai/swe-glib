m4_define([swe_glib_major_version], [1])
m4_define([swe_glib_minor_version], [0])
m4_define([swe_glib_micro_version], [3])
m4_define([swe_glib_version], [swe_glib_major_version.swe_glib_minor_version.swe_glib_micro_version])
m4_define([swe_glib_api_version], [swe_glib_major_version.0])

AC_INIT([SWE-GLib], [swe_glib_version], [gergely@polonkai.eu], [swe-glib])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_HEADERS([config.h])
AM_SILENT_RULES([yes])
AC_ARG_ENABLE(debug, [AC_HELP_STRING([--enable-debug], [compile with debugging support])], , enable_debug=no)

if test "x$enable_debug" = "xyes" ; then
    AC_DEFINE([DEBUG], [1], [Define if debugging is enabled])
fi

AC_SUBST([SWE_GLIB_MAJOR_VERSION], [swe_glib_major_version])
AC_SUBST([SWE_GLIB_MINOR_VERSION], [swe_glib_minor_version])
AC_SUBST([SWE_GLIB_MICRO_VERSION], [swe_glib_micro_version])
AC_SUBST([SWE_GLIB_VERSION], [swe_glib_version])
AC_SUBST([SWE_GLIB_API_VERSION], [swe_glib_api_version])
AC_SUBST([SWE_GLIB_API_VERSION_U], [AS_TR_SH([swe_glib_api_version])])

AC_PROG_CC
AM_PROG_CC_C_O
AM_PROG_AR
AC_PROG_LIBTOOL
IT_PROG_INTLTOOL([0.35.0])
GETTEXT_PACKAGE=swe-glib
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.17])
LT_INIT
AC_CHECK_LIB([m], [atan])
GTK_DOC_CHECK([1.19], [--flavour no-tmpl])
GOBJECT_INTROSPECTION_CHECK([1.0])
PKG_PROG_PKG_CONFIG
AC_PATH_PROG([GLIB_MKENUMS], [glib-mkenums])
PKG_CHECK_MODULES([GLIB], [glib-2.0])
PKG_CHECK_MODULES([GOBJECT], [gobject-2.0])
AC_CONFIG_MACRO_DIR([m4])

LIBSWE_LIBS='$(top_builddir)/swe/src/libswe-1.75.la'
AC_SUBST(LIBSWE_LIBS)

LIBSWE_GLIB_LIBS='$(top_builddir)/src/libswe-glib-$(SWE_GLIB_API_VERSION).la'
AC_SUBST(LIBSWE_GLIB_LIBS)

AC_CONFIG_FILES([
    Makefile
    swe/Makefile
    swe/src/Makefile
    swe/doc/Makefile
    src/Makefile
    data/Makefile
    po/Makefile.in
    docs/reference/swe-glib/version.xml
    docs/reference/swe-glib/Makefile
    data/swe-glib.pc
    data/swe-glib.spec
])
AC_OUTPUT
