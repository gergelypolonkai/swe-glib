/* gswe-aspect-info.c: Aspect related information
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

#include "gswe-types.h"
#include "gswe-aspect-info.h"
#include "gswe-aspect-info-private.h"

/**
 * SECTION:gswe-aspect-info
 * @short_description: a structure storing information about aspects
 * @title: GsweAspectInfo
 * @stability: Stable
 * @include: swe-glib.h
 *
 * The #GsweAspectInfo stores information about an aspect.
 */

void
gswe_aspect_info_free(GsweAspectInfo *aspect_info)
{
    if (aspect_info) {
        if (aspect_info->name) {
            g_free(aspect_info->name);
        }

        g_free(aspect_info);
    }
}

GsweAspectInfo *
gswe_aspect_info_copy(GsweAspectInfo *aspect_info)
{
    GsweAspectInfo *ret;

    if (aspect_info == NULL) {
        return NULL;
    }

    ret = g_new0(GsweAspectInfo, 1);

    ret->aspect       = aspect_info->aspect;
    ret->name         = g_strdup(aspect_info->name);
    ret->size         = aspect_info->size;
    ret->orb_modifier = aspect_info->orb_modifier;
    ret->harmonic     = aspect_info->harmonic;
    ret->major        = aspect_info->major;

    return ret;
}

G_DEFINE_BOXED_TYPE(GsweAspectInfo, gswe_aspect_info, (GBoxedCopyFunc)gswe_aspect_info_copy, (GBoxedFreeFunc)gswe_aspect_info_free);

/**
 * gswe_aspect_info_get_aspect:
 * @aspect_info: (in) (allow-none): a #GsweAspectInfo
 *
 * Gets the aspect ID
 */
GsweAspect
gswe_aspect_info_get_aspect(GsweAspectInfo *aspect_info)
{
    if (aspect_info) {
        return aspect_info->aspect;
    } else {
        return GSWE_ASPECT_NONE;
    }
}

/**
 * gswe_aspect_info_get_name:
 * @aspect_info: (in) (allow-none): a #GsweAspectInfo
 *
 * Gets the name of this aspect. If NLS is enabled, name is translated in
 * gswe_init(), so if you switch locale in your program, it will remain in the
 * old locale. The returned string should not be freed or modified. It remains
 * valid until @aspect_info exists.
 *
 * Returns: (transfer none): the name of the aspect
 */
const gchar *
gswe_aspect_info_get_name(GsweAspectInfo *aspect_info)
{
    if (aspect_info) {
        return aspect_info->name;
    } else {
        return NULL;
    }
}

/**
 * gswe_aspect_info_get_size:
 * @aspect_info: (in) (allow-none): a #GsweAspectInfo
 *
 * Gets the size of the aspect.
 *
 * Returns: the size of the aspect, in degrees
 */
gdouble
gswe_aspect_info_get_size(GsweAspectInfo *aspect_info)
{
    if (aspect_info) {
        return aspect_info->size;
    } else {
        return 0.0;
    }
}

/**
 * gswe_aspect_info_get_orb_modifier:
 * @aspect_info: (in) (allow-none): a #GsweAspectInfo
 *
 * Gets the orb modifier of this aspect. The orb modifier is subtracted from
 * the planets' orb during aspect calculation.
 *
 * Returns: the orb modifier, in degrees
 */
gdouble
gswe_aspect_info_get_orb_modifier(GsweAspectInfo *aspect_info)
{
    if (aspect_info) {
        return aspect_info->orb_modifier;
    } else {
        return 0.0;
    }
}

/**
 * gswe_aspect_info_get_harmonic:
 * @aspect_info: (in) (allow-none): a #GsweAspectInfo
 *
 * Tells if this aspect is considered harmonic.
 *
 * Returns: TRUE if the aspect is harmonic; FALSE otherwise
 */
gboolean
gswe_aspect_info_get_harmonic(GsweAspectInfo *aspect_info)
{
    if (aspect_info) {
        return aspect_info->harmonic;
    } else {
        return FALSE;
    }
}

/**
 * gswe_aspect_info_get_major:
 * @aspect_info: (in) (allow-none): a #GsweAspectInfo
 *
 * Gets the significance of the aspect, e.g. if its Ptolemaic or note.
 *
 * Returns: TRUE if the aspect is a major (Ptolemaic) one; FALSE otherwise
 */
gboolean
gswe_aspect_info_get_major(GsweAspectInfo *aspect_info)
{
    if (aspect_info) {
        return aspect_info->major;
    } else {
        return FALSE;
    }
}

