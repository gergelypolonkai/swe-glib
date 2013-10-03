/* gswe-antiscion-axis-info.c: Antiscion axis related information
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
#include "swe-glib.h"
#include "swe-glib-private.h"
#include "gswe-antiscion-axis-info.h"
#include "gswe-antiscion-axis-info-private.h"

/**
 * SECTION:gswe-antiscion-axis-info
 * @short_description: a structure storing information about antiscion axes
 * @title: GsweAntiscionAxisInfo
 * @stability: Stable
 * @include: swe-glib.h
 *
 * The #GsweAntiscionAxisInfo stores information about an antiscion axis.
 */

G_DEFINE_BOXED_TYPE(GsweAntiscionAxisInfo, gswe_antiscion_axis_info, (GBoxedCopyFunc)gswe_antiscion_axis_info_ref, (GBoxedFreeFunc)gswe_antiscion_axis_info_unref);

static void
gswe_antiscion_axis_info_free(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    if (antiscion_axis_info->name) {
        g_free(antiscion_axis_info->name);
    }

    g_free(antiscion_axis_info);
}

/**
 * gswe_antiscion_axis_info_new:
 *
 * Creates a new #GsweAntiscionAxisInfo object with reference count set to 1.
 *
 * Returns: (transfer full): a new #GsweAntiscionAxisInfo
 */
GsweAntiscionAxisInfo *
gswe_antiscion_axis_info_new(void)
{
    GsweAntiscionAxisInfo *ret;

    ret = g_new0(GsweAntiscionAxisInfo, 1);
    ret->refcount = 1;

    return ret;
}

/**
 * gswe_antiscion_axis_info_ref:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 *
 * Increases reference count on @antiscion_axis_info.
 *
 * Returns: (transfer none): the same #GsweAntiscionAxisInfo
 */
GsweAntiscionAxisInfo *
gswe_antiscion_axis_info_ref(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    antiscion_axis_info->refcount++;

    return antiscion_axis_info;
}

/**
 * gswe_antiscion_axis_info_unref:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 *
 * Decreases reference count on @antiscion_axis_info. If reference count reaches zero, @antiscion_axis_info is freed.
 */
void
gswe_antiscion_axis_info_unref(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    if (--antiscion_axis_info->refcount == 0) {
        gswe_antiscion_axis_info_free(antiscion_axis_info);
    }
}

/**
 * gswe_antiscion_axis_info_set_axis:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 * @axis: the new axis
 *
 * Sets the axis ID.
 */
void
gswe_antiscion_axis_info_set_axis(GsweAntiscionAxisInfo *antiscion_axis_info, GsweAntiscionAxis axis)
{
    antiscion_axis_info->axis = axis;
}

/**
 * gswe_antiscion_axis_info_get_axis:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 *
 * Gets the axis ID.
 *
 * Returns: the axis this #GsweAntiscionAxisInfo represents
 */
GsweAntiscionAxis
gswe_antiscion_axis_info_get_axis(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    return antiscion_axis_info->axis;
}

/**
 * gswe_antiscion_axis_info_set_start_sign_info:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 * @sign_info: a #GsweSignInfo to set as the starting sign of @antiscion_axis_info
 *
 * Sets the starting sign of the axis.
 */
void
gswe_antiscion_axis_info_set_start_sign_info(GsweAntiscionAxisInfo *antiscion_axis_info, GsweSignInfo *sign_info)
{
    if (antiscion_axis_info->start_sign != NULL) {
        gswe_sign_info_unref(antiscion_axis_info->start_sign);
    }

    antiscion_axis_info->start_sign = gswe_sign_info_ref(sign_info);
}

/**
 * gswe_antiscion_axis_info_get_start_sign_info:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 *
 * Gets the starting sign of the axis.
 *
 * Returns: (transfer none): the #GsweSignInfo of the sign in which this axis starts
 */
GsweSignInfo *
gswe_antiscion_axis_info_get_start_sign_info(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    return antiscion_axis_info->start_sign;
}

/**
 * gswe_antiscion_axis_info_set_start_sign:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 * @sign: the new starting sign of @antiscion_axis_info
 * @err: a #GError
 *
 * Sets the starting sign of the axis. Unlike
 * gswe_antiscion_axis_info_set_start_sign(), this method searches through the
 * registered signs for a #GsweSignInfo record, and sets that as the starting
 * sign. @err is populated with GSWE_ERROR_UNKNOWN_SIGN if such record can not
 * be found.
 */
void
gswe_antiscion_axis_info_set_start_sign(GsweAntiscionAxisInfo *antiscion_axis_info, GsweZodiac sign, GError **err)
{
    GsweSignInfo *sign_info;

    if ((sign_info = g_hash_table_lookup(gswe_sign_info_table, GINT_TO_POINTER(sign))) == NULL) {
        g_warning("Trying to fetch an unregistered sign");
        g_set_error(err, GSWE_ERROR, GSWE_ERROR_UNKNOWN_SIGN, "The requested sign is not registered");

        return;
    }

    if (antiscion_axis_info->start_sign != NULL) {
        gswe_sign_info_unref(antiscion_axis_info->start_sign);
    }

    antiscion_axis_info->start_sign = gswe_sign_info_ref(sign_info);
}

/**
 * gswe_antiscion_axis_info_get_start_sign:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 *
 * Gets the starting sign of the axis.
 *
 * Returns: the corresponding sign ID
 */
GsweZodiac
gswe_antiscion_axis_info_get_start_sign(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    if (antiscion_axis_info->start_sign) {
        return antiscion_axis_info->start_sign->sign;
    } else {
        return GSWE_SIGN_NONE;
    }
}

/**
 * gswe_antiscion_axis_info_set_name:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 * @name: the new name of the axis
 *
 * Sets the name of the axis
 */
void
gswe_antiscion_axis_info_set_name(GsweAntiscionAxisInfo *antiscion_axis_info, const gchar *name)
{
    if (antiscion_axis_info->name != NULL) {
        g_free(antiscion_axis_info->name);
    }

    antiscion_axis_info->name = g_strdup(name);
}

/**
 * gswe_antiscion_axis_info_get_name:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 *
 * Gets the name of the axis.
 *
 * Returns: (transfer none): the name of the axis
 */
const gchar *
gswe_antiscion_axis_info_get_name(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    return antiscion_axis_info->name;
}

/**
 * gswe_antiscion_axis_info_set_sign_offset:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 * @sign_offset: the new sign offset, in degree
 *
 * Sets the offset at which the axis starts.
 */
void
gswe_antiscion_axis_info_set_sign_offset(GsweAntiscionAxisInfo *antiscion_axis_info, gdouble sign_offset)
{
    antiscion_axis_info->sign_offset = sign_offset;
}

/**
 * gswe_antiscion_axis_info_get_sign_offset:
 * @antiscion_axis_info: (in): a #GsweAntiscionAxisInfo
 *
 * Gets the offset at which the axis starts.
 *
 * Returns: the offset, in degrees
 */
gdouble
gswe_antiscion_axis_info_get_sign_offset(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    return antiscion_axis_info->sign_offset;
}

