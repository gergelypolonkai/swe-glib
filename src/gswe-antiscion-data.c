/* gswe-antiscion-data.c: Antiscia related data
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
#include "gswe-antiscion-data.h"
#include "gswe-antiscion-data-private.h"

/**
 * SECTION:gswe-antiscion-data
 * @short_description: a structure representing a planet's position-related data
 * @title: GsweAntiscionData
 * @stability: Stable
 * @include: swe-glib.h
 * @see_also: #GsweAntiscionAxisInfo
 *
 * #GsweAntiscionData is a structure that represents an antiscion relationship
 * between two planets, based on a specified axis.
 */

G_DEFINE_BOXED_TYPE(GsweAntiscionData, gswe_antiscion_data, (GBoxedCopyFunc)gswe_antiscion_data_ref, (GBoxedFreeFunc)gswe_antiscion_data_unref);

static void
gswe_antiscion_data_free(GsweAntiscionData *antiscion_data)
{
    if (antiscion_data->planet1) {
        gswe_planet_data_unref(antiscion_data->planet1);
    }

    if (antiscion_data->planet2) {
        gswe_planet_data_unref(antiscion_data->planet2);
    }

    if (antiscion_data->antiscion_axis_info) {
        gswe_antiscion_axis_info_unref(antiscion_data->antiscion_axis_info);
    }
}

/**
 * gswe_antiscion_data_new:
 *
 * Creates a new #GsweAntiscionData object with reference count set to 1.
 *
 * Returns: (transfer full): a new #GsweAntiscionData object
 */
GsweAntiscionData *
gswe_antiscion_data_new(void)
{
    GsweAntiscionData *ret;

    ret = g_new0(GsweAntiscionData, 1);
    ret->refcount = 1;

    return ret;
}

static gboolean
find_antiscion(gpointer axis_p, GsweAntiscionAxisInfo *antiscion_axis_info, GsweAntiscionData *antiscion_data)
{
    GsweAntiscionAxis axis;
    gdouble start_point,
            axis_position,
            planet_orb;

    if ((axis = GPOINTER_TO_INT(axis_p)) == GSWE_ANTISCION_AXIS_NONE) {
        return FALSE;
    }

    planet_orb = fmin(antiscion_data->planet1->planet_info->orb, antiscion_data->planet2->planet_info->orb);
    start_point = (antiscion_axis_info->start_sign->sign - 1) * 30.0;

    start_point += antiscion_axis_info->sign_offset;

    axis_position = 2 * start_point - antiscion_data->planet1->position;

    if (axis_position < 0) {
        axis_position += 360.0;
    }

    if ((antiscion_data->difference = fabs(antiscion_data->planet2->position - axis_position)) <= planet_orb) {
        antiscion_data->antiscion_axis_info = antiscion_axis_info;

        return TRUE;
    } else {
        antiscion_data->difference = 0.0;
    }

    return FALSE;
}

/**
 * gswe_antiscion_data_calculate:
 * @antiscion_data: a #GsweAntiscionData
 *
 * Calculates the antiscion between the planets set in @antiscion_data. Planets
 * can be set either by calling gswe_antiscion_data_set_planet1() and
 * gswe_antiscion_data_set_planet2(), or by creating the #GsweAntiscionData
 * with gswe_antiscion_data_new_with_planets().
 *
 * <note><para>If the object is created by
 * gswe_antiscion_data_new_with_planets(), or when both planets are set by
 * calling gswe_antiscion_data_set_planet1() and
 * gswe_antiscion_data_set_planet2(), the antiscion information is
 * automatically calculated. However, when either planet's data changes, the
 * antiscion data is not calculated automatically, so if you expect the planets
 * to get a new position (e.g. the #GsweTimestamp changes in a #GsweMoment
 * which holds the @antiscion_data, in which case the planet positions are
 * automatically adjusted), this function should be called.</para></note>
 */
void
gswe_antiscion_data_calculate(GsweAntiscionData *antiscion_data)
{
    if ((antiscion_data->antiscion_axis_info = g_hash_table_find(gswe_antiscion_axis_info_table, (GHRFunc)find_antiscion, antiscion_data)) == NULL) {
        antiscion_data->antiscion_axis_info = gswe_antiscion_axis_info_ref(g_hash_table_lookup(gswe_antiscion_axis_info_table, GINT_TO_POINTER(GSWE_ANTISCION_AXIS_NONE)));
    } else {
        gswe_antiscion_axis_info_ref(antiscion_data->antiscion_axis_info);
    }
}

/**
 * gswe_antiscion_data_new_with_planets:
 * @planet1: a #GswePlanetData
 * @planet2: a #GswePlanetData
 *
 * Creates a new #GsweAntiscionData object with both planets initially set. The
 * respective antiscion is instantly calculated.
 *
 * Returns: (transfer full): a new #GsweAntiscionData
 */
GsweAntiscionData *
gswe_antiscion_data_new_with_planets(GswePlanetData *planet1, GswePlanetData *planet2)
{
    GsweAntiscionData *ret;

    ret = gswe_antiscion_data_new();
    ret->planet1 = gswe_planet_data_ref(planet1);
    ret->planet2 = gswe_planet_data_ref(planet2);

    gswe_antiscion_data_calculate(ret);

    return ret;
}

/**
 * gswe_antiscion_data_ref:
 * @antiscion_data: (in): a #GsweAntiscionData
 *
 * Increases reference count on @antiscion_data.
 *
 * Returns: (transfer none): the same #GsweAntiscionData
 */
GsweAntiscionData *
gswe_antiscion_data_ref(GsweAntiscionData *antiscion_data)
{
    antiscion_data->refcount++;

    return antiscion_data;
}

/**
 * gswe_antiscion_data_unref:
 * @antiscion_data: (in): a #GsweAntiscionData
 *
 * Decreases reference count on @antiscion_data. If reference count reaches zero, @antiscion_data is freed.
 */
void
gswe_antiscion_data_unref(GsweAntiscionData *antiscion_data)
{
    if (--antiscion_data->refcount == 0) {
        gswe_antiscion_data_free(antiscion_data);
    }
}

/**
 * gswe_antiscion_data_set_planet1:
 * @antiscion_data: (in): a #GsweAntiscionData
 * @planet1: (in): a #GswePlanetData
 *
 * Sets @planet1 as the first planet of the antiscion.
 */
void
gswe_antiscion_data_set_planet1(GsweAntiscionData *antiscion_data, GswePlanetData *planet1)
{
    if (antiscion_data->planet1) {
        gswe_planet_data_unref(antiscion_data->planet1);
    }

    antiscion_data->planet1 = gswe_planet_data_ref(planet1);
}

/**
 * gswe_antiscion_data_get_planet1:
 * @antiscion_data: (in): a #GsweAntiscionData
 *
 * Gets the first in the antiscion relationship.
 *
 * Returns: (transfer none): The #GswePlanetData associated with the first planet.
 */
GswePlanetData *
gswe_antiscion_data_get_planet1(GsweAntiscionData *antiscion_data)
{
    return antiscion_data->planet1;
}

/**
 * gswe_antiscion_data_set_planet2:
 * @antiscion_data: (in): a #GsweAntiscionData
 * @planet2: (in): a #GswePlanetData
 *
 * Sets @planet2 as the second planet of the antiscion.
 */
void
gswe_antiscion_data_set_planet2(GsweAntiscionData *antiscion_data, GswePlanetData *planet2)
{
    if (antiscion_data->planet2) {
        gswe_planet_data_unref(antiscion_data->planet2);
    }

    antiscion_data->planet2 = gswe_planet_data_ref(planet2);
}

/**
 * gswe_antiscion_data_get_planet2:
 * @antiscion_data: (in): a #GsweAntiscionData
 *
 * Gets the second in the antiscion relationship.
 *
 * Returns: (transfer none): The #GswePlanetData associated with the second planet.
 */
GswePlanetData *
gswe_antiscion_data_get_planet2(GsweAntiscionData *antiscion_data)
{
    return antiscion_data->planet2;
}

/**
 * gswe_antiscion_data_set_axis:
 * @antiscion_data: a #GsweAntiscionData
 * @axis: the axis to set in @antiscion_data
 * @err: a #GError
 *
 * Sets the antiscion axis, which must be known by SWE-GLib (e.g. by calling
 * gswe_init()). @err is populated with GSWE_ERROR_UNKNOWN_ANTISCION_AXIS if
 * the axis is not known.
 */
void
gswe_antiscion_data_set_axis(GsweAntiscionData *antiscion_data, GsweAntiscionAxis axis, GError **err)
{
    GsweAntiscionAxisInfo *antiscion_axis_info;

    if ((antiscion_axis_info = g_hash_table_lookup(gswe_antiscion_axis_info_table, GINT_TO_POINTER(axis))) == NULL) {
        g_set_error(err, GSWE_ERROR, GSWE_ERROR_UNKNOWN_ANTISCION_AXIS, "Unknown antiscion axis");

        return;
    }

    if (antiscion_data->antiscion_axis_info) {
        gswe_antiscion_axis_info_unref(antiscion_data->antiscion_axis_info);
    }

    antiscion_data->antiscion_axis_info = gswe_antiscion_axis_info_ref(antiscion_axis_info);
}

/**
 * gswe_antiscion_data_get_axis:
 * @antiscion_data: (in): a #GsweAntiscionData
 *
 * Gets the axis on which the antiscion relationship exists.
 *
 * Returns: the axis ID
 */
GsweAntiscionAxis
gswe_antiscion_data_get_axis(GsweAntiscionData *antiscion_data)
{
    if (antiscion_data->antiscion_axis_info) {
        return antiscion_data->antiscion_axis_info->axis;
    } else {
        return GSWE_ANTISCION_AXIS_NONE;
    }
}

/**
 * gswe_antiscion_data_set_antiscion_axis_info:
 * @antiscion_data: (in): a #GsweAntiscionData
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 *
 * Sets @antiscion_axis_info as the axis of this #GsweAntiscionData.
 */
void
gswe_antiscion_data_set_antiscion_axis_info(GsweAntiscionData *antiscion_data, GsweAntiscionAxisInfo *antiscion_axis_info)
{
    if (antiscion_data->antiscion_axis_info) {
        gswe_antiscion_axis_info_unref(antiscion_data->antiscion_axis_info);
    }

    antiscion_data->antiscion_axis_info = gswe_antiscion_axis_info_ref(antiscion_axis_info);
}

/**
 * gswe_antiscion_data_get_antiscion_axis_info:
 * @antiscion_data: (in): a #GsweAntiscionData
 *
 * Gets the axis information related to the antiscion relationship's axis.
 *
 * Returns: (transfer none): the #GsweAntiscionAxisInfo associated with this axis
 */
GsweAntiscionAxisInfo *
gswe_antiscion_data_get_antiscion_axis_info(GsweAntiscionData *antiscion_data)
{
    return antiscion_data->antiscion_axis_info;
}

/**
 * gswe_antiscion_data_set_difference:
 * @antiscion_data: a #GsweAntiscionData
 * @difference: the difference from an exact antiscion, in degrees
 *
 * Sets the difference of this antiscion from an exact antiscion.
 */
void
gswe_antiscion_data_set_difference(GsweAntiscionData *antiscion_data, gdouble difference)
{
    antiscion_data->difference = difference;
}

/**
 * gswe_antiscion_data_get_difference:
 * @antiscion_data: (in): a #GsweAntiscionData
 *
 * Gets the difference between an exact antiscion and this antiscion relationship.
 *
 * Returns: the difference, in degrees
 */
gdouble
gswe_antiscion_data_get_difference(GsweAntiscionData *antiscion_data)
{
    return antiscion_data->difference;
}

