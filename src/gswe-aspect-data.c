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
#include <math.h>
#include <glib-object.h>

#include "swe-glib-private.h"
#include "swe-glib.h"
#include "gswe-planet-data-private.h"
#include "gswe-planet-info-private.h"
#include "gswe-aspect-info.h"
#include "gswe-aspect-info-private.h"
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
G_DEFINE_BOXED_TYPE(
        GsweAspectData,
        gswe_aspect_data,
        (GBoxedCopyFunc)gswe_aspect_data_ref,
        (GBoxedFreeFunc)gswe_aspect_data_unref
    );

static void
gswe_aspect_data_free(GsweAspectData *aspect_data)
{
    if (aspect_data->planet1) {
        gswe_planet_data_unref(aspect_data->planet1);
    }

    if (aspect_data->planet2) {
        gswe_planet_data_unref(aspect_data->planet2);
    }

    if (aspect_data->aspect_info) {
        gswe_aspect_info_unref(aspect_data->aspect_info);
    }

    g_free(aspect_data);
}

/*
 * find_aspect:
 * @aspect_p: a pointer made with GINT_TO_POINTER(), holding the aspect ID
 * @aspect_info: a GsweAspectInfo, which will be checked against @aspect_data
 * @aspect_data: a GsweAspectData, whose planets' positions will be checked
 *               against @aspect_info
 *
 * This function is called internally by gswe_aspect_data_calculate() to check
 * if the two planets in @aspect_data are in aspect according to @aspect_info
 */
static gboolean
find_aspect(
        gpointer aspect_p,
        GsweAspectInfo *aspect_info,
        GsweAspectData *aspect_data)
{
    gdouble diff,
            planet_orb,
            aspect_orb;

    diff = fabs(aspect_info->size - aspect_data->distance);
    planet_orb = fmin(
            aspect_data->planet1->planet_info->orb,
            aspect_data->planet2->planet_info->orb
        );
    aspect_orb = fmax(1.0, planet_orb - aspect_info->orb_modifier);

    if (diff < aspect_orb) {
        aspect_data->aspect_info = gswe_aspect_info_ref(aspect_info);

        if (aspect_info->size == 0) {
            aspect_data->difference = (1 - ((360.0 - diff) / 360.0)) * 100.0;
        } else {
            aspect_data->difference = (1
                    - ((aspect_info->size - diff) / aspect_info->size)) * 100.0;
        }

        return TRUE;
    }

    return FALSE;
}

void
gswe_aspect_data_calculate(GsweAspectData *aspect_data)
{
    if ((aspect_data->distance = fabs(
                    aspect_data->planet1->position
                        - aspect_data->planet2->position
                )) > 180.0) {
        aspect_data->distance = 360.0 - aspect_data->distance;
    }

    if ((aspect_data->aspect_info = g_hash_table_find(
                    gswe_aspect_info_table,
                    (GHRFunc)find_aspect, aspect_data
                )) == NULL) {
        aspect_data->aspect_info = gswe_aspect_info_ref(
                g_hash_table_lookup(
                        gswe_aspect_info_table,
                        GINT_TO_POINTER(GSWE_ASPECT_NONE)
                    )
            );
    } else {
        gswe_aspect_info_ref(aspect_data->aspect_info);
    }
}

/**
 * gswe_aspect_data_new:
 *
 * Creates a new #GsweAspectData with reference count set to 1.
 *
 * Returns: (transfer full): a new #GsweAspectData
 */
GsweAspectData *
gswe_aspect_data_new(void)
{
    GsweAspectData *ret;

    gswe_init();

    ret = g_new0(GsweAspectData, 1);
    ret->refcount = 1;

    return ret;
}

/**
 * gswe_aspect_data_new_with_planets:
 * @planet1: (in): a #GswePlanetData
 * @planet2: (in): a #GswePlanetData
 *
 * Creates a new #GsweAspectData with a reference count of 1, and both planets
 * initially set. Also calculates the aspect between them.
 *
 * Returns: (transfer full): a new #GsweAspectData with all data set.
 */
GsweAspectData *
gswe_aspect_data_new_with_planets(
        GswePlanetData *planet1,
        GswePlanetData *planet2)
{
    GsweAspectData *ret;

    ret = gswe_aspect_data_new();
    ret->planet1 = gswe_planet_data_ref(planet1);
    ret->planet2 = gswe_planet_data_ref(planet2);

    gswe_aspect_data_calculate(ret);

    return ret;
}

/**
 * gswe_aspect_data_ref:
 * @aspect_data: a #GsweAspectData
 *
 * Increases reference count of @aspect_data.
 *
 * Returns: (transfer none): the same #GsweAspectData
 */
GsweAspectData *
gswe_aspect_data_ref(GsweAspectData *aspect_data)
{
    aspect_data->refcount++;

    return aspect_data;
}

/**
 * gswe_aspect_data_unref:
 * @aspect_data: (in): a #GsweAspectData
 *
 * Decreases reference count on @aspect_data. If reference count reaches zero,
 * @aspect_data is freed.
 */
void
gswe_aspect_data_unref(GsweAspectData *aspect_data)
{
    if (--aspect_data->refcount == 0) {
        gswe_aspect_data_free(aspect_data);
    }
}

/**
 * gswe_aspect_data_set_planet1:
 * @aspect_data: (in): a #GsweAspectData
 * @planet1: (in): a #GswePlanetData
 *
 * Sets @planet1 as the first planet of the aspect.
 */
void
gswe_aspect_data_set_planet1(
        GsweAspectData *aspect_data,
        GswePlanetData *planet1)
{
    if (aspect_data->planet1) {
        gswe_planet_data_unref(aspect_data->planet1);
    }

    aspect_data->planet1 = gswe_planet_data_ref(planet1);

    if (aspect_data->planet2) {
        gswe_aspect_data_calculate(aspect_data);
    }
}

/**
 * gswe_aspect_data_get_planet1:
 * @aspect_data: (in): a #GsweAspectData
 *
 * Gets the first planet in the aspect.
 *
 * Returns: (transfer none): The #GswePlanetData associated with the first
 * planet
 */
GswePlanetData *
gswe_aspect_data_get_planet1(GsweAspectData *aspect_data)
{
    return aspect_data->planet1;
}

/**
 * gswe_aspect_data_set_planet2:
 * @aspect_data: (in): a #GsweAspectData
 * @planet2: (in): a #GswePlanetData
 *
 * Sets @planet2 as the second planet of the aspect.
 */
void
gswe_aspect_data_set_planet2(
        GsweAspectData *aspect_data,
        GswePlanetData *planet2)
{
    if (aspect_data->planet2) {
        gswe_planet_data_unref(aspect_data->planet2);
    }

    aspect_data->planet2 = gswe_planet_data_ref(planet2);

    if (aspect_data->planet1) {
        gswe_aspect_data_calculate(aspect_data);
    }
}

/**
 * gswe_aspect_data_get_planet2:
 * @aspect_data: (in): a #GsweAspectData
 *
 * Gets the second planet in the aspect.
 *
 * Returns: (transfer none): The #GswePlanetData associated with the second
 * planet
 */
GswePlanetData *
gswe_aspect_data_get_planet2(GsweAspectData *aspect_data)
{
    return aspect_data->planet2;
}

/**
 * gswe_aspect_data_get_distance:
 * @aspect_data: (in): a #GsweAspectData
 *
 * Gets the exact distance between the two planets in the aspect.
 *
 * Returns: the distance, in degrees
 */
gdouble
gswe_aspect_data_get_distance(GsweAspectData *aspect_data)
{
    return aspect_data->distance;
}

/**
 * gswe_aspect_data_get_aspect:
 * @aspect_data: (in): a #GsweAspectData
 *
 * Gets the actual aspect between the two planets.
 *
 * Returns: the aspect ID
 */
GsweAspect
gswe_aspect_data_get_aspect(GsweAspectData *aspect_data)
{
    if (aspect_data->aspect_info) {
        return aspect_data->aspect_info->aspect;
    } else {
        return GSWE_ASPECT_NONE;
    }
}

/**
 * gswe_aspect_data_get_aspect_info:
 * @aspect_data: (in): a #GsweAspectData
 *
 * Gets the the #GsweAspectInfo object for this aspect.
 *
 * Returns: (transfer none): a #GsweAspectInfo
 */
GsweAspectInfo *
gswe_aspect_data_get_aspect_info(GsweAspectData *aspect_data)
{
    return aspect_data->aspect_info;
}

/**
 * gswe_aspect_data_get_difference:
 * @aspect_data: (in): a #GsweAspectData
 *
 * Gets the difference between an exact aspect and this one.
 *
 * Returns: the difference in percent.
 */
gdouble
gswe_aspect_data_get_difference(GsweAspectData *aspect_data)
{
    return aspect_data->difference;
}

