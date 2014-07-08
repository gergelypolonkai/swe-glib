/* gswe-house-system-info.h: House system information
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
#ifndef __SWE_GLIB_GSWE_HOUSE_SYSTEM_INFO_H__
#define __SWE_GLIB_GSWE_HOUSE_SYSTEM_INFO_H__

#include <glib-object.h>

#include "gswe-types.h"

G_BEGIN_DECLS

/**
 * GsweHouseSystemInfo:
 *
 * <structname>GsweHouseSystemInfo</structname> is an opaque structure whose
 * members cannot be accessed directly.
 *
 * Since: 1.1
 */
typedef struct _GsweHouseSystemInfo GsweHouseSystemInfo;

GType gswe_house_system_info_get_type(void);
#define GSWE_TYPE_HOUSE_SYSTEM_INFO (gswe_house_system_info_get_type())

GsweHouseSystemInfo *gswe_house_system_info_new(void);

GsweHouseSystemInfo *gswe_house_system_info_ref(
        GsweHouseSystemInfo *house_system_info);

void gswe_house_system_info_unref(GsweHouseSystemInfo *house_system_info);

void gswe_house_system_info_set_house_system(
        GsweHouseSystemInfo *house_system_info,
        GsweHouseSystem house_system);

GsweHouseSystem gswe_house_system_info_get_house_system(
        GsweHouseSystemInfo *house_system_info);

void gswe_house_system_info_set_sweph_id(
        GsweHouseSystemInfo *house_system_info,
        gchar sweph_id);

gchar gswe_house_system_info_get_sweph_id(
        GsweHouseSystemInfo *house_system_info);

void gswe_house_system_info_set_name(
        GsweHouseSystemInfo *house_system_info,
        const gchar *name);

const gchar *gswe_house_system_info_get_name(
        GsweHouseSystemInfo *house_system_info);

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_HOUSE_SYSTEM_INFO_H__ */

