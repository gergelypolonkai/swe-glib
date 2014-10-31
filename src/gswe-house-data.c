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

#include "swe-glib-private.h"
#include "swe-glib.h"
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

G_DEFINE_BOXED_TYPE(
        GsweHouseData,
        gswe_house_data,
        (GBoxedCopyFunc)gswe_house_data_ref,
        (GBoxedFreeFunc)gswe_house_data_unref
    );

static void
gswe_house_data_free(GsweHouseData *house_data)
{
    if (house_data->sign_info) {
        gswe_sign_info_unref(house_data->sign_info);
    }

    g_free(house_data);
}

/**
 * gswe_house_data_new:
 *
 * Creates a new #GsweHouseData with reference count set to 1.
 *
 * Returns: (transfer full): a new #GsweHouseData
 */
GsweHouseData *
gswe_house_data_new(void)
{
    GsweHouseData *ret;

    ret = g_new0(GsweHouseData, 1);
    ret->refcount = 1;

    return ret;
}

/**
 * gswe_house_data_ref:
 * @house_data: a #GsweHouseData
 *
 * Increases reference count on @house_data by one.
 *
 * Returns: (transfer none): the same #GsweHouseData
 */
GsweHouseData *
gswe_house_data_ref(GsweHouseData *house_data)
{
    house_data->refcount++;

    return house_data;
}

/**
 * gswe_house_data_unref:
 * @house_data: a #GsweHouseData
 *
 * Decreases reference count on @house_data by one. If reference count drops to
 * zero, @house_data is freed.
 */
void
gswe_house_data_unref(GsweHouseData *house_data)
{
    if (house_data == NULL) {
        return;
    }

    if (--house_data->refcount == 0) {
        gswe_house_data_free(house_data);
    }
}

/**
 * gswe_house_data_get_house:
 * @house_data: (in): a #GsweHouseData
 *
 * Gets the number of the house.
 *
 * Returns: the house number
 */
guint
gswe_house_data_get_house(GsweHouseData *house_data)
{
    return house_data->house;
}

/**
 * gswe_house_data_get_cusp_position:
 * @house_data: (in): a #GsweHouseData
 *
 * Gets the position of the house's cusp.
 *
 * Returns: the cusp position, in degrees
 */
gdouble
gswe_house_data_get_cusp_position(GsweHouseData *house_data)
{
    return house_data->cusp_position;
}

/**
 * gswe_house_data_get_sign:
 * @house_data: a #GsweHouseData
 *
 * Gets the sign which the house's cusp is in.
 *
 * Returns: the GsweZodiac of the house cusp's sign
 */
GsweZodiac
gswe_house_data_get_sign(GsweHouseData *house_data)
{
    if (house_data->sign_info) {
        return house_data->sign_info->sign;
    } else {
        return GSWE_SIGN_NONE;
    }
}

/**
 * gswe_house_data_get_sign_info:
 * @house_data: (in): a #GsweHouseData
 *
 * Gets the #GsweSignInfo that represents the sign which the house's cusp is in.
 *
 * Returns: (transfer none): a #GsweSignInfo representing the sign
 */
GsweSignInfo *
gswe_house_data_get_sign_info(GsweHouseData *house_data)
{
    return house_data->sign_info;
}

