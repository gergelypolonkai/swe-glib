/* gswe-version.c: SWE-GLib version information
 *
 * Copyright © 2013  Gergely Polonkai
 *
 * SWE-GLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * SWE-GLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include "gswe-version.h"

/**
 * SECTION:gswe-version
 * @short_description: SWE-GLib version information
 * @title: Version information
 * @stability: Stable
 * @include: swe-glib/swe-glib.h
 *
 * Version information of the SWE-GLib library.
 */

/**
 * GSWE_MAJOR_VERSION:
 *
 * The major version number of the SWE-GLib library.
 */

/**
 * GSWE_MINOR_VERSION:
 *
 * The minor version number of the SWE-GLib library.
 */

/**
 * GSWE_MICRO_VERSION:
 *
 * The micro version number of the SWE-GLib library.
 */

/**
 * GSWE_CHECK_VERSION:
 * @major: the major version to check for
 * @minor: the minor version to check for
 * @micro: the micro version to check for
 *
 * Checks the version number of the SWE-GLib library that is being comipled
 * against.
 *
 * Returns: TRUE if the required version is satisfied; FALSE otherwise.
 */

/**
 * gswe_check_version:
 * @required_major: the required major version
 * @required_minor: the required minor version
 * @required_micro: the required micro version
 *
 * Checks that the SWE-GLib library in use is compatible with the given
 * version.
 *
 * Returns: TRUE if the required version is satisfied; FALSE otherwise.
 */
gboolean
gswe_check_version(guint required_major, guint required_minor, guint required_micro)
{
    return (GSWE_CHECK_VERSION(required_major, required_minor, required_micro));
}

