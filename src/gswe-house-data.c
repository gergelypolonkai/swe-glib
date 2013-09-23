/* gswe-house-data.c: House related data
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

#include "gswe-house-data.h"
#include "gswe-house-data-private.h"

/**
 * SECTION:gswe-house-data
 * @short_description: a structure representing a house's position-related data
 * @title: GsweHouseData
 * @stability: Stable
 * @include: swe-glib.h
 * @see_also: #GsweHouseSystemInfo
 *
 * #GsweHouseData is a structure that represents a house's position.
 */

G_DEFINE_BOXED_TYPE(GsweHouseData, gswe_house_data, (GBoxedCopyFunc)gswe_house_data_copy, (GBoxedFreeFunc)g_free);

GsweHouseData *
gswe_house_data_copy(GsweHouseData *house_data)
{
    GsweHouseData *ret = g_new0(GsweHouseData, 1);

    ret->house = house_data->house;
    ret->cusp_position = house_data->cusp_position;
    ret->sign = house_data->sign;

    return ret;
}

/**
 * gswe_house_data_get_house:
 * @house_data: (in) (allow-none): a #GsweHouseData
 *
 * Gets the number of the house.
 *
 * Returns: the house number
 */
guint
gswe_house_data_get_house(GsweHouseData *house_data)
{
    if (house_data) {
        return house_data->house;
    } else {
        return 0;
    }
}

/**
 * gswe_house_data_get_cusp_position:
 * @house_data: (in) (allow-none): a #GsweHouseData
 *
 * Gets the position of the house's cusp.
 *
 * Returns: the cusp position, in degrees
 */
gdouble
gswe_house_data_get_cusp_position(GsweHouseData *house_data)
{
    if (house_data) {
        return house_data->cusp_position;
    } else {
        return 0.0;
    }
}

/**
 * gswe_house_data_get_sign:
 * @house_data: (in) (allow-none): a #GsweHouseData
 *
 * Gets the sign in which the house's cusp is.
 *
 * Returns: (transfer none): a #GsweSignInfo representing the sign
 */
GsweSignInfo *
gswe_house_data_get_sign(GsweHouseData *house_data)
{
    if (house_data) {
        return house_data->sign;
    } else {
        return NULL;
    }
}

