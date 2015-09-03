include $(top_srcdir)/swe-glib.mk

ACLOCAL_AMFLAGS = -I m4
SUBDIRS = swe swe/src swe/doc src po data tests

if ENABLE_GTK_DOC
SUBDIRS += docs/reference/swe-glib
endif

DISTCHECK_CONFIGURE_FLAGS = --enable-gtk-doc

intltool_extra = intltool-extract.in intltool-merge.in intltool-update.in

EXTRA_DIST += $(intltool_extra) $(header_DATA) autogen.sh

DISTCLEANFILES += intltool-extract intltool-merge intltool-update

MAINTAINERCLEANFILES += ChangeLog

distclean-local:
	if test "$(srcdir)" = "."; then :; else \
	    rm -f ChangeLog; \
	fi

ChangeLog:
	$(AM_V_GEN) if test -d "$(srcdir)/.git"; then \
	    (GIT_DIR=$(top_srcdir)/.git ./missing --run git log -M -C --name-status --date=short --no-color) | fmt --split-only > $@.tmp \
	    && mv -f $@.tmp $@ \
	    || ($(RM) $@.tmp; \
	        echo Failed to generate ChangeLog, your ChangeLog may be outdated >&2; \
	        (test -f $@ || echo git log is required to generate this file >> $@)); \
	else \
	    test -f $@ || \
	    (echo A git checkout and git log is required to generate ChangeLog >&2 && \
	    echo A git checkout and git log is required to generate this file >> $@); \
	fi

.PHONY: ChangeLog

.PHONY: lcov genlcov lcov-clean
# use recursive makes in order to ignore errors during check
lcov:
	-$(MAKE) $(AM_MAKEFLAGS) -k check
	$(MAKE) $(AM_MAKEFLAGS) genlcov

# we have to massage the lcov.info file slightly to hide the effect of libtool
# placing the objects files in the .libs/ directory separate from the *.c
# we also have to delete tests/.libs/libmoduletestplugin_*.gcda
genlcov:
	rm -f $(top_builddir)/tests/.libs/libmoduletestplugin_*.gcda
	$(LTP) --directory $(top_builddir) --capture --output-file glib-lcov.info --test-name GLIB_PERF --no-checksum --compat-libtool
	LANG=C $(LTP_GENHTML) --prefix $(top_builddir) --output-directory glib-lcov --title "GLib Code Coverage" --legend --show-details glib-lcov.info
	@echo "file://$(abs_top_builddir)/glib-lcov/index.html"

lcov-clean:
	-$(LTP) --directory $(top_builddir) -z
	-rm -rf glib-lcov.info glib-lcov
	-find -name '*.gcda' -print | xargs rm

