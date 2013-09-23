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

G_DEFINE_BOXED_TYPE(GsweSignInfo, gswe_sign_info, (GBoxedCopyFunc)gswe_sign_info_copy, (GBoxedFreeFunc)gswe_sign_info_free);

GsweSignInfo *
gswe_sign_info_copy(GsweSignInfo *sign_info)
{
    GsweSignInfo *ret;

    if (sign_info == NULL) {
        return NULL;
    }

    ret = g_new0(GsweSignInfo, 1);

    ret->sign = sign_info->sign;
    ret->name = g_strdup(sign_info->name);
    ret->element = sign_info->element;
    ret->quality = sign_info->quality;

    return ret;
}

void
gswe_sign_info_free(GsweSignInfo *sign_info)
{
    if (sign_info) {
        if (sign_info->name) {
            g_free(sign_info->name);
        }

        g_free(sign_info);
    }
}

/**
 * gswe_sign_info_get_sign:
 * @sign_info: (in) (allow-none): a #GsweSignInfo
 *
 * Gets the sign ID that is represented by this #GsweSignInfo.
 *
 * Returns: the sign ID
 */
GsweZodiac
gswe_sign_info_get_sign(GsweSignInfo *sign_info)
{
    if (sign_info) {
        return sign_info->sign;
    } else {
        return GSWE_SIGN_NONE;
    }
}

/**
 * gswe_sign_info_get_name:
 * @sign_info: (in) (allow-none): a #GsweSignInfo
 *
 * Gets the name associated with this sign.
 *
 * Returns: (transfer none): the name of the zodiac sign
 */
const gchar *
gswe_sign_info_get_name(GsweSignInfo *sign_info)
{
    if (sign_info) {
        return sign_info->name;
    } else {
        return NULL;
    }
}

/**
 * gswe_sign_info_get_element:
 * @sign_info: (in) (allow-none): a #GsweSignInfo
 *
 * Gets the element this sign belongs to.
 *
 * Returns: the element
 */
GsweElement
gswe_sign_info_get_element(GsweSignInfo *sign_info)
{
    if (sign_info) {
        return sign_info->element;
    } else {
        return GSWE_ELEMENT_NONE;
    }
}

/**
 * gswe_sign_info_get_quality:
 * @sign_info: (in) (allow-none): a #GsweSignInfo
 *
 * Gets the quality this sign belongs to.
 *
 * Returns: the quality
 */
GsweQuality
gswe_sign_info_get_quality(GsweSignInfo *sign_info)
{
    if (sign_info) {
        return sign_info->quality;
    } else {
        return GSWE_QUALITY_NONE;
    }
}

