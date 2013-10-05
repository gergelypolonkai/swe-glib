#!/bin/sh
# Run this to generate all the initial makefiles, etc.

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

PKG_NAME="swe-glib"

(test -f $srcdir/configure.ac \
  && test -f $srcdir/src/swe-glib.c) || {
    echo -n "**Error**: Directory "\`$srcdir\'" does not look like the"
    echo " top-level $PKG_NAME directory"
    exit 1
}

m4dir=`grep '^AC_CONFIG_MACRO_DIR' configure.ac | sed -n -e 's/AC_CONFIG_MACRO_DIR(\([^()]*\))/\1/p' | sed -e 's/^\[\(.*\)\]$/\1/' | sed -e 1q`
if [ -n "$m4dir" ]; then
    m4dir="-I $m4dir"
fi

echo "Running libtoolize"
libtoolize --force --copy || exit $?

echo "Running autopoint"
autopoint --force || exit $?

echo "Running intltoolize"
intltoolize --force --copy --automake || exit $?

GTKDOCIZE=$(which gtkdocize 2>/dev/null)
if test -z $GTKDOCIZE; then
    echo "You don't have gtk-doc installed, and thus won't be able to generate the documentation."
    rm -f gtk-doc.make
    rm -f $m4dir/gtk-doc.m4
    cat > gtk-doc.make <<EOF
EXTRA_DIST =
CLEANFILES =
EOF
else
    echo "Running gtkdocize"
    gtkdocize --copy || exit $?
fi

echo "Running aclocal"
aclocal $m4dir $ACLOCAL_FLAGS || exit $?

echo "Running autoconf"
autoconf || exit $?

if grep "^A[CM]_CONFIG_HEADER" configure.ac >/dev/null; then
    echo "Running autoheader"
    autoheader || exit $?
    # this prevents automake from thinking config.h.in is out of
    # date, since autoheader doesn't touch the file if it doesn't
    # change.
    test -f config.h.in && touch config.h.in
fi

echo "Running automake"
automake --gnu --add-missing --copy -Wno-portability || exit $?

