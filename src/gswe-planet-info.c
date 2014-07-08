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

G_DEFINE_BOXED_TYPE(
        GswePlanetInfo,
        gswe_planet_info,
        (GBoxedCopyFunc)gswe_planet_info_ref,
        (GBoxedFreeFunc)gswe_planet_info_unref);

/**
 * gswe_planet_info_new:
 *
 * Creates a new #GswePlanetInfo object with reference count set to 1.
 *
 * Returns: a new #GswePlanetInfo
 */
GswePlanetInfo *
gswe_planet_info_new(void)
{
    GswePlanetInfo *ret;

    ret = g_new0(GswePlanetInfo, 1);
    ret->refcount = 1;

    return ret;
}

/**
 * gswe_planet_info_ref:
 * @planet_info: (in): a #GswePlanetInfo
 *
 * Increases reference count on @planet_info.
 *
 * Returns: (transfer none): the same #GswePlanetData
 */
GswePlanetInfo *
gswe_planet_info_ref(GswePlanetInfo *planet_info)
{
    planet_info->refcount++;

    return planet_info;
}

static void
gswe_planet_info_free(GswePlanetInfo *planet_info)
{
    if (planet_info->name) {
        g_free(planet_info->name);
    }

    g_free(planet_info);
}

/**
 * gswe_planet_info_unref:
 * @planet_info: a #GswePlanetInfo
 *
 * Decreases reference count on @planet_info. If reference count reaches zero,
 * @planet_info is freed.
 */
void
gswe_planet_info_unref(GswePlanetInfo *planet_info)
{
    if (--planet_info->refcount == 0) {
        gswe_planet_info_free(planet_info);
    }
}

/**
 * gswe_planet_info_set_planet:
 * @planet_info: a #GswePlanetInfo
 * @planet: the new planet ID
 *
 * Sets the planet ID that will be represented by @planet_info.
 */
void
gswe_planet_info_set_planet(GswePlanetInfo *planet_info, GswePlanet planet)
{
    planet_info->planet = planet;
}

/**
 * gswe_planet_info_get_planet:
 * @planet_info: (in): A #GswePlanetInfo
 *
 * Gets the planet ID represented by this #GswePlanetInfo.
 *
 * Returns: the planet ID
 */
GswePlanet
gswe_planet_info_get_planet(GswePlanetInfo *planet_info)
{
    return planet_info->planet;
}

/**
 * gswe_planet_info_set_sweph_id:
 * @planet_info: a #GswePlanetInfo
 * @sweph_id: the new Swiss Ephemeris planet ID
 *
 * Sets the Swiss Ephemeris planet_id associated with this planet.
 */
void
gswe_planet_info_set_sweph_id(GswePlanetInfo *planet_info, gint32 sweph_id)
{
    planet_info->sweph_id = sweph_id;
}

/**
 * gswe_planet_info_get_sweph_id:
 * @planet_info: (in): A #GswePlanetInfo
 *
 * Gets the Swiss Ephemeris planet ID associated with this planet.
 *
 * Returns: the Swiss Ephemeris planet ID
 */
gint32
gswe_planet_info_get_sweph_id(GswePlanetInfo *planet_info)
{
    return planet_info->sweph_id;
}

/**
 * gswe_planet_info_set_real_body:
 * @planet_info: a #GswePlanetInfo
 * @real_body: a  boolean that indicates if this planet is an object recognized
 *             by Swiss Ephemeris
 *
 * Sets whether this planet is an object recognized by the Swiss Ephemeris
 * library.
 */
void
gswe_planet_info_set_real_body(GswePlanetInfo *planet_info, gboolean real_body)
{
    planet_info->real_body = real_body;
}

/**
 * gswe_planet_info_get_real_body:
 * @planet_info: (in): A #GswePlanetInfo
 *
 * Checks weather this planet is a real celestial body (e.g. it has a Swiss
 * Ephemeris planet ID) or not.
 *
 * Returns: TRUE if the planet has a Swiss Ephemeris planet ID; FALSE otherwise
 */
gboolean
gswe_planet_info_get_real_body(GswePlanetInfo *planet_info)
{
    return planet_info->real_body;
}

/**
 * gswe_planet_info_set_orb:
 * @planet_info: a #GswePlanetInfo
 * @orb: the planet's own orb
 *
 * Sets the orb of @planet_info. This value is used in aspect and antiscion
 * calculations.
 */
void
gswe_planet_info_set_orb(GswePlanetInfo *planet_info, gdouble orb)
{
    planet_info->orb = orb;
}

/**
 * gswe_planet_info_get_orb:
 * @planet_info: (in): A #GswePlanetInfo
 *
 * Gets the orb of the planet.
 *
 * Returns: the orb, in degrees
 */
gdouble
gswe_planet_info_get_orb(GswePlanetInfo *planet_info)
{
    return planet_info->orb;
}

/**
 * gswe_planet_info_set_name:
 * @planet_info: (in): a #GswePlanetInfo
 * @name: (in): the new name of the planet
 *
 * Sets the name of @planet_info.
 */
void
gswe_planet_info_set_name(GswePlanetInfo *planet_info, const gchar *name)
{
    if (planet_info->name) {
        g_free(planet_info->name);
    }

    planet_info->name = g_strdup(name);
}

/**
 * gswe_planet_info_get_name:
 * @planet_info: (in): A #GswePlanetInfo
 *
 * Gets the name of the planet.
 *
 * Returns: (transfer none): the planet's name
 */
const gchar *
gswe_planet_info_get_name(GswePlanetInfo *planet_info)
{
    return planet_info->name;
}

/**
 * gswe_planet_info_set_points:
 * @planet_info: a #GswePlanetInfo
 * @points: the new point value
 *
 * Sets the point value of @planet_info. This value is used in points
 * calculations.
 */
void
gswe_planet_info_set_points(GswePlanetInfo *planet_info, gint points)
{
    planet_info->points = points;
}

/**
 * gswe_planet_info_get_points:
 * @planet_info: (in): A #GswePlanetInfo
 *
 * Gets the value this planet counts in point calculations.
 *
 * Returns: the point value
 */
gint
gswe_planet_info_get_points(GswePlanetInfo *planet_info)
{
    return planet_info->points;
}

