/* gswe-planet-info.c: Planet related information
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

#include "gswe-planet-info.h"
#include "gswe-planet-info-private.h"

/**
 * SECTION:gswe-planet-info
 * @short_description: a structure storing information about a planet
 * @title: GswePlanetInfo
 * @stability: Stable
 * @include: swe-glib.h
 *
 * The #GswePlanetInfo structure stores information about a planet.
 */

G_DEFINE_BOXED_TYPE(GswePlanetInfo, gswe_planet_info, (GBoxedCopyFunc)gswe_planet_info_copy, (GBoxedFreeFunc)gswe_planet_info_free);

GswePlanetInfo *
gswe_planet_info_copy(GswePlanetInfo *planet_info)
{
    GswePlanetInfo *ret = g_new0(GswePlanetInfo, 1);

    ret->planet = planet_info->planet;
    ret->sweph_id = planet_info->sweph_id;
    ret->real_body = planet_info->real_body;
    ret->orb = planet_info->orb;
    ret->name = g_strdup(planet_info->name);
    ret->points = planet_info->points;

    return ret;
}

void
gswe_planet_info_free(GswePlanetInfo *planet_info)
{
    g_free(planet_info->name);
    g_free(planet_info);
}

/**
 * gswe_planet_info_get_planet:
 * @planet_info: (in) (allow-none): A #GswePlanetInfo
 *
 * Gets the planet ID represented by this #GswePlanetInfo.
 *
 * Returns: the planet ID
 */
GswePlanet
gswe_planet_info_get_planet(GswePlanetInfo *planet_info)
{
    if (planet_info) {
        return planet_info->planet;
    } else {
        return GSWE_PLANET_NONE;
    }
}

/**
 * gswe_planet_info_get_sweph_id:
 * @planet_info: (in) (allow-none): A #GswePlanetInfo
 *
 * Gets the Swiss Ephemeris planet ID associated with this planet.
 *
 * Returns: the Swiss Ephemeris planet ID
 */
gint32
gswe_planet_info_get_sweph_id(GswePlanetInfo *planet_info)
{
    if (planet_info) {
        return planet_info->sweph_id;
    } else {
        return -1;
    }
}

/**
 * gswe_planet_info_get_real_body:
 * @planet_info: (in) (allow-none): A #GswePlanetInfo
 *
 * Checks weather this planet is a real celestial body (e.g. it has a Swiss Ephemeris planet ID) or not.
 *
 * Returns: TRUE if the planet has a Swiss Ephemeris planet ID; FALSE otherwise
 */
gboolean
gswe_planet_info_get_real_body(GswePlanetInfo *planet_info)
{
    if (planet_info) {
        return planet_info->real_body;
    } else {
        return FALSE;
    }
}

/**
 * gswe_planet_info_get_orb:
 * @planet_info: (in) (allow-none): A #GswePlanetInfo
 *
 * Gets the orb of the planet.
 *
 * Returns: the orb, in degrees
 */
gdouble
gswe_planet_info_get_orb(GswePlanetInfo *planet_info)
{
    if (planet_info) {
        return planet_info->orb;
    } else {
        return -1.0;
    }
}

/**
 * gswe_planet_info_get_name:
 * @planet_info: (in) (allow-none): A #GswePlanetInfo
 *
 * Gets the name of the planet.
 *
 * Returns: (transfer none): the planet's name
 */
const gchar *
gswe_planet_info_get_name(GswePlanetInfo *planet_info)
{
    if (planet_info) {
        return planet_info->name;
    } else {
        return NULL;
    }
}

/**
 * gswe_planet_info_get_points:
 * @planet_info: (in) (allow-none): A #GswePlanetInfo
 *
 * Gets the value this planet counts in point calculations.
 *
 * Returns: the point value
 */
gint
gswe_planet_info_get_points(GswePlanetInfo *planet_info)
{
    if (planet_info) {
        return planet_info->points;
    } else {
        return 0;
    }
}

