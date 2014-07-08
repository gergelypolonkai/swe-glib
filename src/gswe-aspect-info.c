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
 * @short_description: a structure storing information about an aspect
 * @title: GsweAspectInfo
 * @stability: Stable
 * @include: swe-glib.h
 *
 * The #GsweAspectInfo stores information about an aspect.
 *
 * <warning><para>Using set_* type of funcions on an already registered
 * #GsweAspectInfo can currently cause undocumented side effects, if a
 * #GsweMoment is already instantiated. Currently, this covers all
 * #GsweAspectInfo objects. In the future, registering custom aspects may be
 * possible; until then, you should never use such functions.</para></warning>
 */

G_DEFINE_BOXED_TYPE(
        GsweAspectInfo,
        gswe_aspect_info,
        (GBoxedCopyFunc)gswe_aspect_info_ref,
        (GBoxedFreeFunc)gswe_aspect_info_unref
    );

static void
gswe_aspect_info_free(GsweAspectInfo *aspect_info)
{
    if (aspect_info->name) {
        g_free(aspect_info->name);
    }

    g_free(aspect_info);
}

/**
 * gswe_aspect_info_new:
 *
 * Creates a new #GsweAspectInfo with reference count set to 1.
 *
 * Returns: (transfer full): a new #GsweAspectInfo
 */
GsweAspectInfo *
gswe_aspect_info_new(void)
{
    GsweAspectInfo *ret;

    ret = g_new0(GsweAspectInfo, 1);
    ret->refcount = 1;

    return ret;
}

/**
 * gswe_aspect_info_ref:
 * @aspect_info: (in): a #GsweAspectInfo
 *
 * Increases reference count on @aspect_info by one.
 *
 * Returns: (transfer none): the same #GsweAspectInfo
 */
GsweAspectInfo *
gswe_aspect_info_ref(GsweAspectInfo *aspect_info)
{
    aspect_info->refcount++;

    return aspect_info;
}

/**
 * gswe_aspect_info_unref:
 * @aspect_info: (in): a #GsweAspectInfo
 *
 * Decreases reference count of @aspect_info by one. If reference count drops
 * to zero, @aspect_info is freed.
 */
void
gswe_aspect_info_unref(GsweAspectInfo *aspect_info)
{
    if (--aspect_info->refcount == 0) {
        gswe_aspect_info_free(aspect_info);
    }
}

/**
 * gswe_aspect_info_set_aspect:
 * @aspect_info: (in): a #GsweAspectInfo
 * @aspect: the aspect to set in @aspect_info
 *
 * Sets @aspect_info to represenc @aspect.
 */
void
gswe_aspect_info_set_aspect(GsweAspectInfo *aspect_info, GsweAspect aspect)
{
    aspect_info->aspect = aspect;
}

/**
 * gswe_aspect_info_get_aspect:
 * @aspect_info: (in): a #GsweAspectInfo
 *
 * Gets the aspect ID
 */
GsweAspect
gswe_aspect_info_get_aspect(GsweAspectInfo *aspect_info)
{
    return aspect_info->aspect;
}

/**
 * gswe_aspect_info_set_name:
 * @aspect_info: (in): a #GsweAspectInfo
 * @name: (in): the name to be set as @aspect_info’s name
 *
 * Sets the name of @aspect_info to @name.
 */
void
gswe_aspect_info_set_name(GsweAspectInfo *aspect_info, const gchar *name)
{
    if (aspect_info->name) {
        g_free(aspect_info->name);
    }

    aspect_info->name = g_strdup(name);
}

/**
 * gswe_aspect_info_get_name:
 * @aspect_info: (in): a #GsweAspectInfo
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
    return aspect_info->name;
}

/**
 * gswe_aspect_info_set_size:
 * @aspect_info: (in): a #GsweAspectInfo
 * @size: the new size for @aspect_info, in degrees
 *
 * Sets the size of @aspect info.
 */
void
gswe_aspect_info_set_size(GsweAspectInfo *aspect_info, gdouble size)
{
    aspect_info->size = size;
}

/**
 * gswe_aspect_info_get_size:
 * @aspect_info: (in): a #GsweAspectInfo
 *
 * Gets the size of the aspect.
 *
 * Returns: the size of the aspect, in degrees
 */
gdouble
gswe_aspect_info_get_size(GsweAspectInfo *aspect_info)
{
    return aspect_info->size;
}

/**
 * gswe_aspect_info_set_orb_modifier:
 * @aspect_info: (in): a #GsweAspectInfo
 * @orb_modifier: the new orb modifier of @aspect_info
 *
 * Sets the orb modifier for @aspect_info. The orb modifier is used in aspect
 * calculation; if the difference between an exact aspect and the distance
 * between two positions exceeds this limit, the aspect is not considered.
 */
void
gswe_aspect_info_set_orb_modifier(
        GsweAspectInfo *aspect_info,
        gdouble orb_modifier)
{
    aspect_info->orb_modifier = orb_modifier;
}

/**
 * gswe_aspect_info_get_orb_modifier:
 * @aspect_info: (in): a #GsweAspectInfo
 *
 * Gets the orb modifier of this aspect. The orb modifier is subtracted from
 * the planets' orb during aspect calculation.
 *
 * Returns: the orb modifier, in degrees
 */
gdouble
gswe_aspect_info_get_orb_modifier(GsweAspectInfo *aspect_info)
{
    return aspect_info->orb_modifier;
}

/**
 * gswe_aspect_info_set_harmonic:
 * @aspect_info: (in): a #GsweAspectInfo
 * @harmonic: TRUE, if @aspect_info should be considered harmonic; FALSE
 *            otherwise
 *
 * Sets the harmonic state of @aspect_info.
 */
void
gswe_aspect_info_set_harmonic(GsweAspectInfo *aspect_info, gboolean harmonic)
{
    aspect_info->harmonic = harmonic;
}

/**
 * gswe_aspect_info_get_harmonic:
 * @aspect_info: (in): a #GsweAspectInfo
 *
 * Tells if this aspect is considered harmonic.
 *
 * Returns: TRUE if the aspect is harmonic; FALSE otherwise
 */
gboolean
gswe_aspect_info_get_harmonic(GsweAspectInfo *aspect_info)
{
    return aspect_info->harmonic;
}

/**
 * gswe_aspect_info_set_major:
 * @aspect_info: (in): a #GsweAspectInfo
 * @major: TRUE, if @aspect_info should be considered major (Ptolemaic); FALSE
 *         otherwise
 *
 * Sets the major state of @aspect_info.
 *
 * <note><para>As all Ptolemaic aspects are registered during gswe_init(), you
 * should never set @major to TRUE on new aspects.</para></note>
 */
void
gswe_aspect_info_set_major(GsweAspectInfo *aspect_info, gboolean major)
{
    aspect_info->major = major;
}

/**
 * gswe_aspect_info_get_major:
 * @aspect_info: (in): a #GsweAspectInfo
 *
 * Gets the significance of the aspect, e.g. if its Ptolemaic or note.
 *
 * Returns: TRUE if the aspect is a major (Ptolemaic) one; FALSE otherwise
 */
gboolean
gswe_aspect_info_get_major(GsweAspectInfo *aspect_info)
{
    return aspect_info->major;
}

