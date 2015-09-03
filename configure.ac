m4_define([swe_glib_major_version], [2])
m4_define([swe_glib_minor_version], [1])
m4_define([swe_glib_micro_version], [0])
m4_define([swe_glib_version], [swe_glib_major_version.swe_glib_minor_version.swe_glib_micro_version])
m4_define([swe_glib_api_version], [swe_glib_major_version.0])
m4_define([swe_major_version], [2])
m4_define([swe_minor_version], [0])
m4_define([swe_version], [swe_major_version.swe_minor_version])

AC_INIT([SWE-GLib], [swe_glib_version], [gergely@polonkai.eu], [swe-glib])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_HEADERS([config.h])
AM_SILENT_RULES([yes])

dnl ********************************
dnl *** Enable debugging support ***
dnl ********************************
AC_ARG_ENABLE(debug,
  AC_HELP_STRING([--enable-debug],
                 [compile with debugging support]),
  [enable_debug=$enableval], [enable_debug=no])

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
AC_SUBST([SWE_VERSION], [swe_version])

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
m4_ifdef([VALA_PROG_VAPIGEN], [
VALA_PROG_VAPIGEN([0.21])
AM_CONDITIONAL([HAVE_VAPIGEN], true)
],[
AM_CONDITIONAL([HAVE_VAPIGEN], false)
])
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

dnl ************************************
dnl *** Enable lcov coverage reports ***
dnl ************************************

AC_ARG_ENABLE(coverage,
  AS_HELP_STRING([--enable-coverage],
                 [enable coverage testing with gcov]),
  [use_gcov=$enableval], [use_gcov=no])

AS_IF([ test "x$use_gcov" = "xyes"], [
  dnl we need gcc:
  if test "$GCC" != "yes"; then
    AC_MSG_ERROR([GCC is required for --enable-coverage])
  fi

  dnl Check if ccache is being used
  AC_CHECK_PROG(SHTOOL, shtool, shtool)
  case `$SHTOOL path $CC` in
    *ccache*[)] gcc_ccache=yes;;
    *[)] gcc_ccache=no;;
  esac

  if test "$gcc_ccache" = "yes" && (test -z "$CCACHE_DISABLE" || test "$CCACHE_DISABLE" != "1"); then
    AC_MSG_ERROR([ccache must be disabled when --enable-coverage option is used. You can disable ccache by setting environment variable CCACHE_DISABLE=1.])
  fi

  ltp_version_list="1.6 1.7 1.8 1.9 1.10"
  AC_CHECK_PROG(LTP, lcov, lcov)
  AC_CHECK_PROG(LTP_GENHTML, genhtml, genhtml)

  AS_IF([ test "$LTP" ], [
    AC_CACHE_CHECK([for ltp version], sw_glib_cv_ltp_version, [
      swe_glib_cv_ltp_version=invalid
      ltp_version=`$LTP -v 2>/dev/null | $SED -e 's/^.* //'`
      for ltp_check_version in $ltp_version_list; do
        if test "$ltp_version" = "$ltp_check_version"; then
          swe_glib_cv_ltp_version="$ltp_check_version (ok)"
        fi
      done
    ])
  ], [
    ltp_msg="To enable code coverage reporting you must have one of the following LTP versions installed: $ltp_version_list"
    AC_MSG_ERROR([$ltp_msg])
  ])

  case $swe_glib_cv_ltp_version in
    ""|invalid[)]
      ltp_msg="You must have one of the following versions of LTP: $ltp_version_list (found: $ltp_version)."
      AC_MSG_ERROR([$ltp_msg])
      LTP="exit 0;"
      ;;
  esac

  if test -z "$LTP_GENHTML"; then
    AC_MSG_ERROR([Could not find genhtml from the LTP package])
  fi

  dnl Remove all optimization flags from CFLAGS
  changequote({,})
  CFLAGS=`echo "$CFLAGS" | $SED -e 's/-O[0-9]*//g'`
  changequote([,])

  dnl Add the special gcc flags
  CFLAGS="$CFLAGS -O0 -fprofile-arcs -ftest-coverage"
  LDFLAGS="$LDFLAGS -lgcov"
])

if test "x$enable_debug" = "xyes" ; then
    AC_DEFINE([DEBUG], [1], [Define if debugging is enabled])
    if test x$cflags_set != xset ; then
        case " $CFLAGS " in
            *[[\ \	]]-g[[\ \	]]*) ;;
            *) CFLAGS="$CFLAGS -g" ;;
        esac
    fi
fi

PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.32.0])
PKG_CHECK_MODULES([GOBJECT], [gobject-2.0 >= 2.32.0])
PKG_CHECK_MODULES([GIO], [gio-2.0 >= 2.26])

AC_ARG_ENABLE(coverage,
  AS_HELP_STRING([--enable-coverage],
                 [enable coverage testing with gcov]),
  [use_gcov=$enableval], [use_gcov=no])

AS_IF([ test "x$use_gcov" = "xyes" ], [
  dnl we need gcc:
  if test "$GCC" != "yes"; then
    AC_MSG_ERROR([GCC is required for --enable-coverage])
  fi

  dnl check if ccache is being used
  AC_CHECK_PROG(SHTOOL, shtool, shtool)

  if test -n "$SHTOOL"; then
    case `$SHTOOL path $CC` in
      *ccache*[)] gcc_ccache=yes ;;
      *[)] gcc_ccached=no ;;
    esac

    if test "$gcc_ccache" = "yes"; then
      AC_MSG_ERROR([ccache must be disabled when --enable-coverage option is used. You can disable ccache by setting the environment variable CCACHE_DISABLED=1])
    fi
  fi

  ltp_version_list="1.6 1.7 1.8 1.9 1.10 1.11"
  AC_CHECK_PROG(LTP, lcov, lcov)
  AC_CHECK_PROG(LTP_GENHTML, genhtml, genhtml)

  AS_IF([ test "$LTP" ], [
    AC_CACHE_CHECK([for ltp version], glib_cv_ltp_version, [
      glib_cv_ltp_version=invalid
      ltp_version=`$LTP -v 2>/dev/null | $SED -e 's/^.* //'`
      for ltp_check_version in $ltp_version_list; do
        if test "$ltp_version" = "$ltp_check_version"; then
          glib_cv_ltp_version="$ltp_check_version (ok)"
        fi
      done
    ])
  ], [
    ltp_msg="To enable code coverage reporting you must have one of the following LTP versions installed: $ltp_version_list"
    AC_MSG_ERROR([$ltp_msg])
  ])

  case $glib_cv_ltp_version in
    ""|invalid[)]
      ltp_msg="You must have one of the following versions of LTP: $ltp_version_list (found: $ltp_version)."
      AC_MSG_ERROR([$ltp_msg])
      LTP="exit 0;"
      ;;
  esac

  if test -z "$LTP_GENHTML"; then
    AC_MSG_ERROR([Could not find genhtml from the LTP package])
  fi

  dnl Remove all optimization flags from CFLAGS
  changequote({,})
  CFLAGS=`echo "$CFLAGS" | $SED -e 's/-O[0-9]*//g'`
  changequote([,])

  dnl Add the special gcc flags
  CFLAGS="$CFLAGS -O0 -fprofile-arcs -ftest-coverage"
  LDFLAGS="$LDFLAGS -lgcov"
])

GLIB_GSETTINGS
AC_CONFIG_MACRO_DIR([m4])

LIBSWE_LIBS='$(top_builddir)/swe/src/libswe-$(SWE_VERSION).la'
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
    src/gswe-version.h
])
AM_COND_IF([ENABLE_GTK_DOC], [
    AC_CONFIG_FILES([
        docs/reference/swe-glib/version.xml
        docs/reference/swe-glib/Makefile
    ])
])
AC_OUTPUT
