/* gswe-antiscion-data.c: Antiscia related data
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
#include <glib-object.h>

#include "gswe-antiscion-data.h"
#include "gswe-antiscion-data-private.h"

/**
 * SECTION:gswe-antiscion-data
 * @short_description: a structure representing a planet's position-related data
 * @title: GsweAntiscionData
 * @stability: Stable
 * @include: swe-glib.h
 * @see_also: #GsweAntiscionInfo
 *
 * #GsweAntiscionData is a structure that represents an antiscion relationship
 * between two planets, based on a specified axis.
 */

GsweAntiscionData *
gswe_antiscion_data_copy(GsweAntiscionData *antiscion_data)
{
    GsweAntiscionData *ret = g_new0(GsweAntiscionData, 1);

    ret->planet1 = antiscion_data->planet1;
    ret->planet2 = antiscion_data->planet2;
    ret->axis = antiscion_data->axis;
    ret->antiscion_axis_info = antiscion_data->antiscion_axis_info;
    ret->difference = antiscion_data->difference;

    return ret;
}

G_DEFINE_BOXED_TYPE(GsweAntiscionData, gswe_antiscion_data, (GBoxedCopyFunc)gswe_antiscion_data_copy, (GBoxedFreeFunc)g_free);

/**
 * gswe_antiscion_data_get_planet1:
 * @antiscion_data: a #GsweAntiscionData
 *
 * Gets the first in the antiscion relationship.
 *
 * Returns: (transfer none): The #GswePlanetData associated with the first planet.
 */
GswePlanetData *
gswe_antiscion_data_get_planet1(GsweAntiscionData *antiscion_data)
{
    if (antiscion_data) {
        return antiscion_data->planet1;
    } else {
        return NULL;
    }
}

/**
 * gswe_antiscion_data_get_planet2:
 * @antiscion_data: a #GsweAntiscionData
 *
 * Gets the second in the antiscion relationship.
 *
 * Returns: (transfer none): The #GswePlanetData associated with the second planet.
 */
GswePlanetData *
gswe_antiscion_data_get_planet2(GsweAntiscionData *antiscion_data)
{
    if (antiscion_data) {
        return antiscion_data->planet2;
    } else {
        return NULL;
    }
}

/**
 * gswe_antiscion_data_get_axis:
 * @antiscion_data: a #GsweAntiscionData
 *
 * Gets the axis on which the antiscion relationship exists.
 *
 * Returns: the axis ID
 */
GsweAntiscionAxis
gswe_antiscion_data_get_axis(GsweAntiscionData *antiscion_data)
{
    if (antiscion_data) {
        return antiscion_data->axis;
    } else {
        return GSWE_ANTISCION_AXIS_NONE;
    }
}

/**
 * gswe_antiscion_data_get_antiscion_axis_info:
 * @antiscion_data: a #GsweAntiscionData
 *
 * Gets the axis information related to the antiscion relationship's axis.
 *
 * Returns: (transfer none): the #GsweAntiscionInfo associated with this axis
 */
GsweAntiscionAxisInfo *
gswe_antiscion_data_get_antiscion_axis_info(GsweAntiscionData *antiscion_data)
{
    if (antiscion_data) {
        return antiscion_data->antiscion_axis_info;
    } else {
        return NULL;
    }
}

/**
 * gswe_antiscion_data_get_difference:
 * @antiscion_data: a #GsweAntiscionData
 *
 * Gets the difference between an exact antiscion and this antiscion relationship.
 *
 * Returns: the difference, in degrees
 */
gdouble
gswe_antiscion_data_get_difference(GsweAntiscionData *antiscion_data)
{
    if (antiscion_data) {
        return antiscion_data->difference;
    } else {
        return 0.0;
    }
}

