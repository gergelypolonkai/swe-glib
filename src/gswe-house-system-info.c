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

G_DEFINE_BOXED_TYPE(GsweHouseSystemInfo, gswe_house_system_info, (GBoxedCopyFunc)gswe_house_system_info_copy, (GBoxedFreeFunc)gswe_house_system_info_free);

GsweHouseSystemInfo *
gswe_house_system_info_copy(GsweHouseSystemInfo *house_system_info)
{
    GsweHouseSystemInfo *ret;

    if (house_system_info == NULL) {
        return NULL;
    }

    ret               = g_new0(GsweHouseSystemInfo, 1);
    ret->house_system = house_system_info->house_system;
    ret->sweph_id     = house_system_info->sweph_id;
    ret->name         = g_strdup(house_system_info->name);

    return ret;
}

void
gswe_house_system_info_free(GsweHouseSystemInfo *house_system_info)
{
    if (house_system_info) {
        if (house_system_info->name) {
            g_free(house_system_info->name);
        }

        g_free(house_system_info);
    }
}

/**
 * gswe_house_system_info_get_house_system:
 * @house_system_info: (in) (allow-none): a #GsweHouseSystemInfo
 *
 * Gets the house system ID this #GsweHouseSystemInfo represents.
 *
 * Returns: the house system ID
 */
GsweHouseSystem
gswe_house_system_info_get_house_system(GsweHouseSystemInfo *house_system_info)
{
    if (house_system_info) {
        return house_system_info->house_system;
    } else {
        return GSWE_HOUSE_SYSTEM_NONE;
    }
}

/**
 * gswe_house_system_info_get_sweph_id:
 * @house_system_info: (in) (allow-none): a #GsweHouseSystemInfo
 *
 * Gets the Swiss Ephemeris ID for the house system.
 *
 * Returns: the character representing this house system in Swiss Ephemeris
 */
gchar
gswe_house_system_info_get_sweph_id(GsweHouseSystemInfo *house_system_info)
{
    if (house_system_info) {
        return house_system_info->sweph_id;
    } else {
        return 0;
    }
}

/**
 * gswe_house_system_info_get_name:
 * @house_system_info: (in) (allow-none): a #GsweHouseSystemInfo
 *
 * Gets the name of the house system.
 *
 * Returns: (transfer none): the name of the house system
 */
const gchar *
gswe_house_system_info_get_name(GsweHouseSystemInfo *house_system_info)
{
    if (house_system_info) {
        return house_system_info->name;
    } else {
        return NULL;
    }
}

