# SWE-GLib - GLib wrapper around the Swiss Ephemeris library
#
# Most of this file is got from GLib, especially the code coverage measurement
# parts

GTESTER = gtester
GTESTER_REPORT = gtester-report
NULL =

# initialize variables for unconditional += appending
BUILT_SOURCES =
BUILT_EXTRA_DIST =
CLEANFILES = *.log *.trs *.gcda
DISTCLEANFILES =
MAINTAINERCLEANFILES =
EXTRA_DIST =
TEST_PROGS =

noinst_LTLIBRARIES =
noinst_PROGRAMS =
noinst_SCRIPTS =
noinst_DATA =

check_LTLIBRARIES =
check_PROGRAMS =
check_SCRIPTS =
check_DATA =

TESTS =

# test-nonrecursive: run tests only in cwd
if OS_UNIX
test-nonrecursive: ${TEST_PROGS}
	@test -z "${TEST_PROGS}" || G_TEST_SRCDIR="$(abs_srcdir)" G_TEST_BUILDDIR="$(abs_builddir)" G_DEBUG=gc-friendly MALLOC_CHECK_=2 MALLOC_PERTURB_=$$(($${RANDOM:-256} % 256)) ${GTESTER} --verbose ${TEST_PROGS}
else
test-nonrecursive:
endif

.PHONY: test-nonrecursive lcov genlcov lcov-clean
# use recursive makes in order to ignore errors during check
lcov:
	-$(MAKE) $(AM_MAKEFLAGS) -k check
	$(MAKE) $(AM_MAKEFLAGS) genlcov

# we have to massage the lcov.info file slightly to hide the effect of libtool
# placing the objects files in the .libs/ directory separate from the *.c
# we also have to delete tests/.libs/libmoduletestplugin_*.gcda
genlcov:
	$(AM_V_GEN) rm -f $(top_builddir)/tests/.libs/libmoduletestplugin_*.gcda; \
	  $(LTP) --quiet --directory $(top_builddir) --capture --output-file swe-glib-lcov.info --test-name SWE_GLIB_PERF --no-checksum --compat-libtool --ignore-errors source; \
	  $(LTP) --quiet --output-file swe-glib-lcov.info --remove swe-glib-lcov.info docs/reference/\* /tmp/\* ; \
	  LANG=C $(LTP_GENHTML) --quiet --prefix $(top_builddir) --output-directory swe-glib-lcov --title "SWE-GLib Code Coverage" --legend --frames --show-details swe-glib-lcov.info --ignore-errors source
	@echo "file://$(abs_top_builddir)/swe-glib-lcov/index.html"

lcov-clean:
	if test -n "$(LTP)"; then \
	  $(LTP) --quiet --directory $(top_builddir) -z; \
	fi

# run tests in cwd as part of make check
check-local: test-nonrecursive

TEST_PROGS += $(strip $(test_programs) $(test_scripts) $(uninstalled_test_programs) $(uninstalled_test_scripts) \
                      $(dist_test_scripts) $(dist_uninstalled_test_scripts))

if OS_WIN32
TESTS += $(test_programs) $(test_scripts) $(uninstalled_test_programs) $(uninstalled_test_scripts) \
         $(dist_test_scripts) $(dist_uninstalled_test_scripts)
endif

# Note: build even the installed-only targets during 'make check' to ensure that they still work.
# We need to do a bit of trickery here and manage disting via EXTRA_DIST instead of using dist_ prefixes to
# prevent automake from mistreating gmake functions like $(wildcard ...) and $(addprefix ...) as if they were
# filenames, including removing duplicate instances of the opening part before the space, eg. '$(addprefix'.
all_test_programs     = $(test_programs) $(uninstalled_test_programs) $(installed_test_programs) \
                        $(test_extra_programs) $(uninstalled_test_extra_programs) $(installed_test_extra_programs)
all_test_scripts      = $(test_scripts) $(uninstalled_test_scripts) $(installed_test_scripts) \
                        $(test_extra_scripts) $(uninstalled_test_extra_scripts) $(installed_test_extra_scripts)
all_dist_test_scripts = $(dist_test_scripts) $(dist_uninstalled_test_scripts) $(dist_installed_test_scripts) \
                        $(dist_test_extra_scripts) $(dist_uninstalled_test_extra_scripts) $(dist_installed_test_extra_scripts)
all_test_scripts     += $(all_dist_test_scripts)
EXTRA_DIST           += $(all_dist_test_scripts)
all_test_data         = $(test_data) $(uninstalled_test_data) $(installed_test_data)
all_dist_test_data    = $(dist_test_data) $(dist_uninstalled_test_data) $(dist_installed_test_data)
all_test_data        += $(all_dist_test_data)
EXTRA_DIST           += $(all_dist_test_data)
all_test_ltlibs       = $(test_ltlibraries) $(uninstalled_test_ltlibraries) $(installed_test_ltlibraries)

check_LTLIBRARIES += $(all_test_ltlibs)
check_PROGRAMS += $(all_test_programs)
check_SCRIPTS += $(all_test_scripts)
check_DATA += $(all_test_data)
