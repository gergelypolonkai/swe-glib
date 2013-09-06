m4_define([swe_glib_api_version], [1.0])

AC_INIT([swe-glib], [1.0], [gergely@polonkai.eu])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall foreign])
AM_SILENT_RULES([yes])
AC_ARG_ENABLE(debug, [AC_HELP_STRING([--enable-debug], [compile with debugging support])], , enable_debug=no)

if test "x$enable_debug" = "xyes" ; then
    AC_DEFINE([DEBUG], [1], [Define if debugging is enabled])
fi

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

LIBSWE_GLIB_LIBS='$(top_builddir)/src/libswe-glib-0.1.la'
AC_SUBST(LIBSWE_GLIB_LIBS)

AC_CONFIG_FILES([
    Makefile
    swe/src/Makefile
    src/Makefile
    po/Makefile.in
    docs/reference/swe-glib/Makefile
    swe-glib.pc
])
AC_OUTPUT
