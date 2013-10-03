/* gswe-sign-info.c: Zodiac sign related information
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

#include "gswe-sign-info.h"
#include "gswe-sign-info-private.h"

/**
 * SECTION:gswe-sign-info
 * @short_description: a structure storing information about a zodiac sign
 * @title: GsweSignInfo
 * @stability: Stable
 * @include: swe-glib.h
 *
 * The #GsweSignInfo stores information about a zodiac sign.
 */

G_DEFINE_BOXED_TYPE(GsweSignInfo, gswe_sign_info, (GBoxedCopyFunc)gswe_sign_info_ref, (GBoxedFreeFunc)gswe_sign_info_unref);

static void
gswe_sign_info_free(GsweSignInfo *sign_info)
{
    if (sign_info->name) {
        g_free(sign_info->name);
    }

    g_free(sign_info);
}

/**
 * gswe_sign_info_new:
 *
 * Creates a new GsweSignInfo object with reference count set to 1.
 *
 * Returns: (transfer full): a new #GsweSignInfo
 */
GsweSignInfo *
gswe_sign_info_new(void)
{
    GsweSignInfo *ret;

    ret = g_new0(GsweSignInfo, 1);
    ret->refcount = 1;

    return ret;
}

/**
 * gswe_sign_info_ref:
 * @sign_info: (in): a #GsweSignInfo
 *
 * Increases reference count on @sign_info.
 *
 * Returns: (transfer none): the same #GsweSignInfo
 */
GsweSignInfo *
gswe_sign_info_ref(GsweSignInfo *sign_info)
{
    sign_info->refcount++;

    return sign_info;
}

/**
 * gswe_sign_info_unref:
 * @sign_info: a #GsweSignInfo
 *
 * Decreases reference count or @sign_info. If reference count reaches zero, @sign_info is freed.
 */
void
gswe_sign_info_unref(GsweSignInfo *sign_info)
{
    if (--sign_info->refcount == 0) {
        gswe_sign_info_free(sign_info);
    }
}

/**
 * gswe_sign_info_set_sign:
 * @sign_info: (in): a #GsweSignInfo
 * @sign: the sign to set in @sign_info
 *
 * Sets the sign ID that is represented by this #GsweSignInfo.
 */
void
gswe_sign_info_set_sign(GsweSignInfo *sign_info, GsweZodiac sign)
{
    sign_info->sign = sign;
}

/**
 * gswe_sign_info_get_sign:
 * @sign_info: (in): a #GsweSignInfo
 *
 * Gets the sign ID that is represented by this #GsweSignInfo.
 *
 * Returns: the sign ID
 */
GsweZodiac
gswe_sign_info_get_sign(GsweSignInfo *sign_info)
{
    return sign_info->sign;
}

/**
 * gswe_sign_info_set_name:
 * @sign_info: (in): a #GsweSignInfo
 * @name: (in): the name of the sign
 *
 * Sets the name of the sign.
 */
void
gswe_sign_info_set_name(GsweSignInfo *sign_info, const gchar *name)
{
    if (sign_info->name) {
        g_free(sign_info->name);
    }

    sign_info->name = g_strdup(name);
}

/**
 * gswe_sign_info_get_name:
 * @sign_info: (in): a #GsweSignInfo
 *
 * Gets the name associated with this sign.
 *
 * Returns: (transfer none): the name of the zodiac sign
 */
const gchar *
gswe_sign_info_get_name(GsweSignInfo *sign_info)
{
    return sign_info->name;
}

/**
 * gswe_sign_info_set_element:
 * @sign_info: (in): a #GsweSignInfo
 * @element: a #GsweElement
 *
 * Sets the element @sign_info should belong to.
 */
void
gswe_sign_info_set_element(GsweSignInfo *sign_info, GsweElement element)
{
    sign_info->element = element;
}

/**
 * gswe_sign_info_get_element:
 * @sign_info: (in): a #GsweSignInfo
 *
 * Gets the element this sign belongs to.
 *
 * Returns: the element
 */
GsweElement
gswe_sign_info_get_element(GsweSignInfo *sign_info)
{
    return sign_info->element;
}

/**
 * gswe_sign_info_set_quality:
 * @sign_info: (in): a #GsweSignInfo
 * @quality: a #GsweQuality
 *
 * Sets the quality @sign should belong to
 */
void
gswe_sign_info_set_quality(GsweSignInfo *sign_info, GsweQuality quality)
{
    sign_info->quality = quality;
}

/**
 * gswe_sign_info_get_quality:
 * @sign_info: (in): a #GsweSignInfo
 *
 * Gets the quality this sign belongs to.
 *
 * Returns: the quality
 */
GsweQuality
gswe_sign_info_get_quality(GsweSignInfo *sign_info)
{
    return sign_info->quality;
}

