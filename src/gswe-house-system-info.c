/* gswe-house-system-info.c: House system information
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
#include "gswe-house-system-info.h"
#include "gswe-house-system-info-private.h"

/**
 * SECTION:gswe-house-system-info
 * @short_description: a structure storing information about a house system
 * @title: GsweHouseSystemInfo
 * @stability: Stable
 * @include: swe-glib.h
 *
 * #GsweHouseSystemInfo stores information of a house system.
 */

G_DEFINE_BOXED_TYPE(GsweHouseSystemInfo, gswe_house_system_info, (GBoxedCopyFunc)gswe_house_system_info_ref, (GBoxedFreeFunc)gswe_house_system_info_unref);

static void
gswe_house_system_info_free(GsweHouseSystemInfo *house_system_info)
{
    if (house_system_info->name) {
        g_free(house_system_info->name);
    }

    g_free(house_system_info);
}

/**
 * gswe_house_system_info_new:
 *
 * Creates a new #GsweHouseSystemInfo with reference count of 1.
 *
 * Returns: (transfer full): a new #GsweHouseSystemInfo
 */
GsweHouseSystemInfo *
gswe_house_system_info_new(void)
{
    GsweHouseSystemInfo *ret;

    ret = g_new0(GsweHouseSystemInfo, 1);
    ret->refcount = 1;

    return ret;
}

/**
 * gswe_house_system_info_ref:
 * @house_system_info: (in): a #GsweHouseSystemInfo
 *
 * Increases reference count on @house_system_info by one.
 *
 * Returns: (transfer none): the same #GsweHouseSystemInfo
 */
GsweHouseSystemInfo *
gswe_house_system_info_ref(GsweHouseSystemInfo *house_system_info)
{
    house_system_info->refcount++;

    return house_system_info;
}

/**
 * gswe_house_system_info_unref:
 * @house_system_info: a #GsweHouseSystemInfo
 *
 * Decreases reference count on @house_system_info by one. If reference count
 * drops to zero, @house_system_info is freed.
 */
void
gswe_house_system_info_unref(GsweHouseSystemInfo *house_system_info)
{
    if (--house_system_info->refcount == 0) {
        gswe_house_system_info_free(house_system_info);
    }
}

/**
 * gswe_house_system_info_set_house_system:
 * @house_system_info: (in): a #GsweHouseSystemInfo
 * @house_system: a #GsweHouseSystem
 *
 * Sets up @house_system_info to represent @house_system.
 */
void
gswe_house_system_info_set_house_system(GsweHouseSystemInfo *house_system_info, GsweHouseSystem house_system)
{
    house_system_info->house_system = house_system;
}

/**
 * gswe_house_system_info_get_house_system:
 * @house_system_info: (in): a #GsweHouseSystemInfo
 *
 * Gets the house system ID this #GsweHouseSystemInfo represents.
 *
 * Returns: the house system ID
 */
GsweHouseSystem
gswe_house_system_info_get_house_system(GsweHouseSystemInfo *house_system_info)
{
    return house_system_info->house_system;
}

/**
 * gswe_house_system_info_set_sweph_id:
 * @house_system_info: a #GsweHouseSystemInfo
 * @sweph_id: a character recognized by Swiss Ephemeris as a house system
 *
 * Sets up @house_system_info to represent the Swiss Ephemeris house system
 * marked by @sweph_id.
 */
void
gswe_house_system_info_set_sweph_id(GsweHouseSystemInfo *house_system_info, gchar sweph_id)
{
    house_system_info->sweph_id = sweph_id;
}

/**
 * gswe_house_system_info_get_sweph_id:
 * @house_system_info: (in): a #GsweHouseSystemInfo
 *
 * Gets the Swiss Ephemeris ID for the house system.
 *
 * Returns: the character representing this house system in Swiss Ephemeris
 */
gchar
gswe_house_system_info_get_sweph_id(GsweHouseSystemInfo *house_system_info)
{
    return house_system_info->sweph_id;
}

/**
 * gswe_house_system_info_set_name:
 * @house_system_info: a #GsweHouseSystemInfo
 * @name: the new name for this house system
 *
 * Sets the name of @house_system_info.
 */
void
gswe_house_system_info_set_name(GsweHouseSystemInfo *house_system_info, const gchar *name)
{
    if (house_system_info->name) {
        g_free(house_system_info->name);
    }

    house_system_info->name = g_strdup(name);
}

/**
 * gswe_house_system_info_get_name:
 * @house_system_info: (in): a #GsweHouseSystemInfo
 *
 * Gets the name of the house system.
 *
 * Returns: (transfer none): the name of the house system
 */
const gchar *
gswe_house_system_info_get_name(GsweHouseSystemInfo *house_system_info)
{
    return house_system_info->name;
}

