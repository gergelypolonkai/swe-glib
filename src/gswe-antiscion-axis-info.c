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

G_DEFINE_BOXED_TYPE(GsweAntiscionAxisInfo, gswe_antiscion_axis_info, (GBoxedCopyFunc)gswe_antiscion_axis_info_copy, (GBoxedFreeFunc)gswe_antiscion_axis_info_free);

GsweAntiscionAxisInfo *
gswe_antiscion_axis_info_copy(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    GsweAntiscionAxisInfo *ret;

    if (antiscion_axis_info == NULL) {
        return NULL;
    }

    ret = g_new0(GsweAntiscionAxisInfo, 1);
    ret->axis = antiscion_axis_info->axis;
    ret->start_sign = antiscion_axis_info->start_sign;
    ret->name = g_strdup(antiscion_axis_info->name);
    ret->sign_offset = antiscion_axis_info->sign_offset;

    return ret;
}

void
gswe_antiscion_axis_info_free(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    if (antiscion_axis_info) {
        if (antiscion_axis_info->name) {
            g_free(antiscion_axis_info->name);
        }

        g_free(antiscion_axis_info);
    }
}

/**
 * gswe_antiscion_axis_info_get_axis:
 * @antiscion_axis_info: (in) (allow-none): a #GsweAntiscionAxisInfo
 *
 * Gets the axis ID.
 *
 * Returns: the axis this #GsweAntiscionAxisInfo represents
 */
GsweAntiscionAxis
gswe_antiscion_axis_info_get_axis(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    if (antiscion_axis_info) {
        return antiscion_axis_info->axis;
    } else {
        return GSWE_ANTISCION_AXIS_NONE;
    }
}

/**
 * gswe_antiscion_axis_info_get_start_sign:
 * @antiscion_axis_info: (in) (allow-none): a #GsweAntiscionAxisInfo
 *
 * Gets the starting sign of the axis.
 *
 * Returns: (transfer none): the #GsweSignInfo of the sign in which this axis starts
 */
GsweSignInfo *
gswe_antiscion_axis_info_get_start_sign(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    if (antiscion_axis_info) {
        return antiscion_axis_info->start_sign;
    } else {
        return NULL;
    }
}

/**
 * gswe_antiscion_axis_info_get_name:
 * @antiscion_axis_info: (in) (allow-none): a #GsweAntiscionAxisInfo
 *
 * Gets the name of the axis.
 *
 * Returns: (transfer none): the name of the axis
 */
const gchar *
gswe_antiscion_axis_info_get_name(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    if (antiscion_axis_info) {
        return antiscion_axis_info->name;
    } else {
        return NULL;
    }
}

/**
 * gswe_antiscion_axis_info_get_sign_offset:
 * @antiscion_axis_info: (in) (allow-none): a #GsweAntiscionAxisInfo
 *
 * Gets the offset at which the axis starts.
 *
 * Returns: the offset, in degrees
 */
gboolean
gswe_antiscion_axis_info_get_sign_offset(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    if (antiscion_axis_info) {
        return antiscion_axis_info->sign_offset;
    } else {
        return 0.0;
    }
}

