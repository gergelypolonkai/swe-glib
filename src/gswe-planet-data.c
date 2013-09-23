/* gswe-planet-data.c: Planetary positions
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

#include "gswe-planet-data.h"
#include "gswe-planet-data-private.h"

/**
 * SECTION:gswe-planet-data
 * @short_description: a structure representing a planet's position-related data
 * @title: GswePlanetData
 * @stability: Stable
 * @include: swe-glib.h
 * @see_also: #GswePlanetInfo
 *
 * #GswePlanetData is a structure that represents a planet's position-related
 * data, like its actual position on the sky or the house and sign the planet
 * is in.
 */

G_DEFINE_BOXED_TYPE(GswePlanetData, gswe_planet_data, (GBoxedCopyFunc)gswe_planet_data_copy, (GBoxedFreeFunc)g_free);

GswePlanetData *
gswe_planet_data_copy(GswePlanetData *planet_data)
{
    GswePlanetData *ret = g_new0(GswePlanetData, 1);

    ret->planet = planet_data->planet;
    ret->planet_info = planet_data->planet_info;
    ret->position = planet_data->position;
    ret->retrograde = planet_data->retrograde;
    ret->house = planet_data->house;
    ret->sign = planet_data->sign;
    ret->revision = planet_data->revision;

    return ret;
}

/**
 * gswe_planet_data_get_planet:
 * @planet_data: (in) (allow-none): a #GswePlanetData
 *
 * Gets the planet ID for this #GswePlanetData.
 *
 * Returns: the planet ID
 */
GswePlanet
gswe_planet_data_get_planet(GswePlanetData *planet_data)
{
    if (planet_data) {
        return planet_data->planet;
    } else {
        return GSWE_PLANET_NONE;
    }
}

/**
 * gswe_planet_data_get_planet_info:
 * @planet_data: (in) (allow-none): a #GswePlanetData
 *
 * Gets the planet info related to this #GswePlanetData.
 *
 * Returns: (transfer none): the #GswePlanetInfo associated with this planet
 */
GswePlanetInfo *
gswe_planet_data_get_planet_info(GswePlanetData *planet_data)
{
    if (planet_data) {
        return planet_data->planet_info;
    } else {
        return NULL;
    }
}

/**
 * gswe_planet_data_get_position:
 * @planet_data: (in) (allow-none): a #GswePlanetData
 *
 * Gets the position of the planet on the sky.
 *
 * Returns: the position, in degrees
 */
gdouble
gswe_planet_data_get_position(GswePlanetData *planet_data)
{
    if (planet_data) {
        return planet_data->position;
    } else {
        return -1.0;
    }
}

/**
 * gswe_planet_data_get_retrograde:
 * @planet_data: (in) (allow-none): a #GswePlanetData
 *
 * Returns the planet's retrograde status, e.g. if it looks like it moves
 * backwards on the sky.
 *
 * Returns: TRUE, if the planet is in retrograde motion; FALSE otherwise
 */
gboolean
gswe_planet_data_get_retrograde(GswePlanetData *planet_data)
{
    if (planet_data) {
        return planet_data->retrograde;
    } else {
        return FALSE;
    }
}

/**
 * gswe_planet_data_get_house:
 * @planet_data: (in) (allow-none): a #GswePlanetData
 *
 * Gets the house number which the planet is in.
 *
 * Returns: a house number
 */
gint
gswe_planet_data_get_house(GswePlanetData *planet_data)
{
    if (planet_data) {
        return planet_data->house;
    } else {
        return 0;
    }
}

/**
 * gswe_planet_data_get_sign:
 * @planet_data: (in) (allow-none): a #GswePlanetData
 *
 * Gets the sign which the planet is in.
 *
 * Returns: (transfer none): a #GsweSignInfo
 */
GsweSignInfo *
gswe_planet_data_get_sign(GswePlanetData *planet_data)
{
    if (planet_data) {
        return planet_data->sign;
    } else {
        return NULL;
    }
}

