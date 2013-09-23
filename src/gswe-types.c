/* gswe-types.h - Basic types of SWE-GLib
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
#include "gswe-types.h"


GsweCoordinates *
gswe_coordinates_copy(GsweCoordinates *coordinates)
{
    GsweCoordinates *ret = g_new0(GsweCoordinates, 1);

    ret->longitude = coordinates->longitude;
    ret->latitude = coordinates->latitude;
    ret->altitude = coordinates->altitude;

    return ret;
}

G_DEFINE_BOXED_TYPE(GsweCoordinates, gswe_coordinates, (GBoxedCopyFunc)gswe_coordinates_copy, (GBoxedFreeFunc)g_free);

