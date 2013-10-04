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

GTKDOCIZE=$(which gtkdocize 2>/dev/null)
if test -z $GTKDOCIZE; then
        echo "You don't have gtk-doc installed, and thus won't be able to generate the documentation."
        rm -f gtk-doc.make
        cat > gtk-doc.make <<EOF
EXTRA_DIST =
CLEANFILES =
EOF
else
        gtkdocize || exit $?
fi

which gnome-autogen.sh || {
    echo "gnome-autogen.sh not found, you need to install gnome-common"
    exit 1
}

REQUIRED_AUTOMAKE_VERSION=1.9 . gnome-autogen.sh

