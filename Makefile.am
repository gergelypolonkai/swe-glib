ACLOCAL_AMFLAGS = -I m4
SUBDIRS = swe/src src docs/reference/swe-glib

DISTCHECK_CONFIGURE_FLAGS = --enable-gtk-doc

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = swe-glib.pc $(NULL)

headerdir = $(includedir)/swe-glib
header_DATA = src/swe-glib.h $(NULL)

MAINTAINERCLEANFILES = ChangeLog

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

-include $(top_srcdir)/git.mk
