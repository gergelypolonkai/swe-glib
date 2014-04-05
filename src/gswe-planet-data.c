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

#include "swe-glib-private.h"
#include "swe-glib.h"
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

G_DEFINE_BOXED_TYPE(GswePlanetData, gswe_planet_data, (GBoxedCopyFunc)gswe_planet_data_ref, (GBoxedFreeFunc)gswe_planet_data_unref);

static void
gswe_planet_data_free(GswePlanetData *planet_data)
{
    if (planet_data->planet_info) {
        gswe_planet_info_unref(planet_data->planet_info);
    }

    if (planet_data->sign_info) {
        gswe_sign_info_unref(planet_data->sign_info);
    }

    g_free(planet_data);
}

/**
 * gswe_planet_data_new:
 *
 * Creates a new #GswePlanetData object with reference count set to 1.
 *
 * Returns: (transfer full): a new #GswePlanetData
 */
GswePlanetData *
gswe_planet_data_new(void)
{
    GswePlanetData *ret;

    ret = g_new0(GswePlanetData, 1);
    ret->refcount = 1;

    return ret;
}

/**
 * gswe_planet_data_ref:
 * @planet_data: a #GswePlanetData
 *
 * Increases reference count on @planet_data by one.
 *
 * Returns: (transfer none): the same #GswePlanetData
 */
GswePlanetData *
gswe_planet_data_ref(GswePlanetData *planet_data)
{
    planet_data->refcount++;

    return planet_data;
}

/**
 * gswe_planet_data_unref:
 * @planet_data: a #GswePlanetData
 *
 * Decreases reference count on @planet_data by one. If reference count drops to zero, @planet_data is freed.
 */
void
gswe_planet_data_unref(GswePlanetData *planet_data)
{
    if (--planet_data->refcount == 0) {
        gswe_planet_data_free(planet_data);
    }
}

/**
 * gswe_planet_data_set_planet:
 * @planet_data: (in): a #GswePlanetData
 * @planet: the planet to add
 * @err: a #GError
 *
 * Sets @planet as the planet ID of @planet_data. @planet must be registered
 * via gswe_init(); otherwise, @err is populated with
 * GSWE_ERROR_UNKNOWN_PLANET, and the planet ID is not set.
 */
void
gswe_planet_data_set_planet(GswePlanetData *planet_data, GswePlanet planet, GError **err)
{
    GswePlanetInfo *planet_info;

    if ((planet_info = g_hash_table_lookup(gswe_planet_info_table, GINT_TO_POINTER(planet))) == NULL) {
        g_set_error(err, GSWE_ERROR, GSWE_ERROR_UNKNOWN_PLANET, "Planet is unknown");

        return;
    }

    if (planet_data->planet_info) {
        gswe_planet_info_unref(planet_data->planet_info);
    }

    planet_data->planet_info = gswe_planet_info_ref(planet_info);
}

/**
 * gswe_planet_data_get_planet:
 * @planet_data: (in): a #GswePlanetData
 *
 * Gets the planet ID for this #GswePlanetData.
 *
 * Returns: the planet ID
 */
GswePlanet
gswe_planet_data_get_planet(GswePlanetData *planet_data)
{
    if (planet_data == NULL) {
        return GSWE_PLANET_NONE;
    }

    if (planet_data->planet_info) {
        return planet_data->planet_info->planet;
    } else {
        return GSWE_PLANET_NONE;
    }
}

/**
 * gswe_planet_data_set_planet_info:
 * @planet_data: a #GswePlanetData
 * @planet_info: a #GswePlanetInfo
 *
 * Sets @planet_info as the planet information for @planet_data.
 */
void
gswe_planet_data_set_planet_info(GswePlanetData *planet_data, GswePlanetInfo *planet_info)
{
    if (planet_data == NULL) {
        return;
    }

    if (planet_data->planet_info) {
        gswe_planet_info_unref(planet_data->planet_info);
    }

    planet_data->planet_info = gswe_planet_info_ref(planet_info);
}

/**
 * gswe_planet_data_get_planet_info:
 * @planet_data: (in): a #GswePlanetData
 *
 * Gets the planet info related to this #GswePlanetData.
 *
 * Returns: (transfer none): the #GswePlanetInfo associated with this planet
 */
GswePlanetInfo *
gswe_planet_data_get_planet_info(GswePlanetData *planet_data)
{
    if (planet_data == NULL) {
        return NULL;
    }

    return planet_data->planet_info;
}

/**
 * gswe_planet_data_get_position:
 * @planet_data: (in): a #GswePlanetData
 *
 * Gets the position of the planet on the sky.
 *
 * Returns: the position, in degrees
 */
gdouble
gswe_planet_data_get_position(GswePlanetData *planet_data)
{
    if (planet_data == NULL) {
        return 0.0;
    }

    return planet_data->position;
}

/**
 * gswe_planet_data_get_retrograde:
 * @planet_data: (in): a #GswePlanetData
 *
 * Returns the planet's retrograde status, e.g. if it looks like it moves
 * backwards on the sky.
 *
 * Returns: TRUE, if the planet is in retrograde motion; FALSE otherwise
 */
gboolean
gswe_planet_data_get_retrograde(GswePlanetData *planet_data)
{
    if (planet_data == NULL) {
        return FALSE;
    }

    return planet_data->retrograde;
}

/**
 * gswe_planet_data_get_house:
 * @planet_data: (in): a #GswePlanetData
 *
 * Gets the house number which the planet is in.
 *
 * Returns: a house number
 */
guint
gswe_planet_data_get_house(GswePlanetData *planet_data)
{
    if (planet_data == NULL) {
        return 0;
    }

    return planet_data->house;
}

/**
 * gswe_planet_data_get_sign:
 * @planet_data: a #GswePlanetData
 *
 * Gets the zodiac sign in which the planet is currently in. If the planet's data is not calculated yet, this function yields GSWE_PLANET_NONE.
 *
 * Returns: a #GsweZodiac, which @planet_data is currently in
 */
GsweZodiac
gswe_planet_data_get_sign(GswePlanetData *planet_data)
{
    if (planet_data == NULL) {
        return GSWE_SIGN_NONE;
    }

    if (planet_data->sign_info) {
        return planet_data->sign_info->sign;
    } else {
        return GSWE_SIGN_NONE;
    }
}

/**
 * gswe_planet_data_get_sign_info:
 * @planet_data: (in): a #GswePlanetData
 *
 * Gets the sign which the planet is in.
 *
 * Returns: (transfer none): a #GsweSignInfo
 */
GsweSignInfo *
gswe_planet_data_get_sign_info(GswePlanetData *planet_data)
{
    if (planet_data == NULL) {
        return NULL;
    }

    return planet_data->sign_info;
}

