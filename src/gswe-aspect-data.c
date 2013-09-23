/* gswe-aspect-data.c: Aspect related data
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

#include "gswe-aspect-data.h"
#include "gswe-aspect-data-private.h"

/**
 * SECTION:gswe-aspect-data
 * @short_description: a structure representing an aspect between two planets
 * @title: GsweAspectData
 * @stability: Stable
 * @include: swe-glib.h
 * @see_also: #GsweAspectInfo
 *
 * #GsweAspectData is a structure that represents two planets relation to each
 * other, like their aspect and the aspect's difference from an exact aspect.
 */
G_DEFINE_BOXED_TYPE(GsweAspectData, gswe_aspect_data, (GBoxedCopyFunc)gswe_aspect_data_copy, (GBoxedFreeFunc)g_free);

GsweAspectData *
gswe_aspect_data_copy(GsweAspectData *aspect_data)
{
    GsweAspectData *ret;

    if (aspect_data == NULL) {
        return NULL;
    }

    ret = g_new0(GsweAspectData, 1);

    ret->planet1 = aspect_data->planet1;
    ret->planet2 = aspect_data->planet2;
    ret->distance = aspect_data->distance;
    ret->aspect = aspect_data->aspect;
    ret->aspect_info = aspect_data->aspect_info;
    ret->difference = aspect_data->difference;

    return ret;
}

/**
 * gswe_aspect_data_get_planet1:
 * @aspect_data: (in) (allow-none): a #GsweAspectData
 *
 * Gets the first planet in the aspect.
 *
 * Returns: (transfer none): The #GswePlanetData associated with the first planet
 */
GswePlanetData *
gswe_aspect_data_get_planet1(GsweAspectData *aspect_data)
{
    if (aspect_data) {
        return aspect_data->planet1;
    } else {
        return NULL;
    }
}

/**
 * gswe_aspect_data_get_planet2:
 * @aspect_data: (in) (allow-none): a #GsweAspectData
 *
 * Gets the second planet in the aspect.
 *
 * Returns: (transfer none): The #GswePlanetData associated with the second planet
 */
GswePlanetData *
gswe_aspect_data_get_planet2(GsweAspectData *aspect_data)
{
    if (aspect_data) {
        return aspect_data->planet2;
    } else {
        return NULL;
    }
}

/**
 * gswe_aspect_data_get_distance:
 * @aspect_data: (in) (allow-none): a #GsweAspectData
 *
 * Gets the exact distance between the two planets in the aspect.
 *
 * Returns: the distance, in degrees
 */
gdouble
gswe_aspect_data_get_distance(GsweAspectData *aspect_data)
{
    if (aspect_data) {
        return aspect_data->distance;
    } else {
        return -1.0;
    }
}

/**
 * gswe_aspect_data_get_aspect:
 * @aspect_data: (in) (allow-none): a #GsweAspectData
 *
 * Gets the actual aspect between the two planets.
 *
 * Returns: the aspect ID
 */
GsweAspect
gswe_aspect_data_get_aspect(GsweAspectData *aspect_data)
{
    if (aspect_data) {
        return aspect_data->aspect;
    } else {
        return GSWE_ASPECT_NONE;
    }
}

/**
 * gswe_aspect_data_get_aspect_info:
 * @aspect_data: (in) (allow-none): a #GsweAspectData
 *
 * Gets the the #GsweAspectInfo object for this aspect.
 *
 * Returns: (transfer none): a #GsweAspectInfo
 */
GsweAspectInfo *
gswe_aspect_data_get_aspect_info(GsweAspectData *aspect_data)
{
    if (aspect_data) {
        return aspect_data->aspect_info;
    } else {
        return NULL;
    }
}

/**
 * gswe_aspect_data_get_difference:
 * @aspect_data: (in) (allow-none): a #GsweAspectData
 *
 * Gets the difference between an exact aspect and this one.
 *
 * Returns: the difference in pertent.
 */
gdouble
gswe_aspect_data_get_difference(GsweAspectData *aspect_data)
{
    if (aspect_data) {
        return aspect_data->difference;
    } else {
        return -1.0;
    }
}

