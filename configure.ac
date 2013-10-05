m4_define([swe_glib_major_version], [2])
m4_define([swe_glib_minor_version], [0])
m4_define([swe_glib_micro_version], [0])
m4_define([swe_glib_version], [swe_glib_major_version.swe_glib_minor_version.swe_glib_micro_version])
m4_define([swe_glib_api_version], [swe_glib_major_version.0])

AC_INIT([SWE-GLib], [swe_glib_version], [gergely@polonkai.eu], [swe-glib])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_HEADERS([config.h])
AM_SILENT_RULES([yes])
AC_ARG_ENABLE(debug, [AC_HELP_STRING([--enable-debug], [compile with debugging support])], , enable_debug=no)

if test "x$enable_debug" = "xyes" ; then
    AC_DEFINE([DEBUG], [1], [Define if debugging is enabled])
    if test x$cflags_set != xset ; then
        case " $CFLAGS " in
            *[[\ \	]]-g[[\ \	]]*) ;;
            *) CFLAGS="$CFLAGS -g" ;;
        esac
    fi
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
m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.19], [--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])
GOBJECT_INTROSPECTION_CHECK([1.0])
PKG_PROG_PKG_CONFIG
AC_PATH_PROG([GLIB_MKENUMS], [glib-mkenums])
AC_CANONICAL_HOST
native_win32=no
case "$host" in
    *-*-mingw*)
        native_win32=yes
        ;;
esac
AM_CONDITIONAL(OS_WIN32, [test "$native_win32" = "yes"])
AM_CONDITIONAL(OS_UNIX, [test "$native_win32" != "yes"])
AC_PATH_PROG([GTESTER], [gtester])
AC_PATH_PROG([GTESTER_REPORT], [gtester-report])
PKG_CHECK_MODULES([GLIB], [glib-2.0])
PKG_CHECK_MODULES([GOBJECT], [gobject-2.0])
AC_CONFIG_MACRO_DIR([m4])

LIBSWE_LIBS='$(top_builddir)/swe/src/libswe-1.76.la'
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
    tests/Makefile
    data/swe-glib.pc
    data/swe-glib.spec
])
AM_COND_IF([ENABLE_GTK_DOC], [
    AC_CONFIG_FILES([
        docs/reference/swe-glib/version.xml
        docs/reference/swe-glib/Makefile
    ])
])
AC_OUTPUT
