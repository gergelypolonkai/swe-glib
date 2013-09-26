/* gswe-sign-info.h: Zodiac sign related information
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
#ifndef __SWE_GLIB_GSWE_SIGN_INFO_H__
#define __SWE_GLIB_GSWE_SIGN_INFO_H__

#include <glib-object.h>

#include "gswe-types.h"

G_BEGIN_DECLS

/**
 * GsweSignInfo:
 *
 * <structname>GsweSignInfo</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 1.1
 */
typedef struct _GsweSignInfo GsweSignInfo;

GType gswe_sign_info_get_type(void);
#define GSWE_TYPE_SIGN_INFO (gswe_sign_info_get_type())

GsweSignInfo *gswe_sign_info_new(void);

GsweSignInfo *gswe_sign_info_ref(GsweSignInfo *sign_info);
void gswe_sign_info_unref(GsweSignInfo *sign_info);

void gswe_sign_info_set_sign(GsweSignInfo *sign_info, GsweZodiac sign);
GsweZodiac gswe_sign_info_get_sign(GsweSignInfo *sign_info);

void gswe_sign_info_set_name(GsweSignInfo *sign_info, const gchar *name);
const gchar *gswe_sign_info_get_name(GsweSignInfo *sign_info);

void gswe_sign_info_set_element(GsweSignInfo *sign_info, GsweElement element);
GsweElement gswe_sign_info_get_element(GsweSignInfo *sign_info);

void gswe_sign_info_set_quality(GsweSignInfo *sign_info, GsweQuality quality);
GsweQuality gswe_sign_info_get_quality(GsweSignInfo *sign_info);

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_SIGN_INFO_H__ */

