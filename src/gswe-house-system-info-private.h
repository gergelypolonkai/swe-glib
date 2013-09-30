/* gswe-house-system-info-private.h: Private parts of GsweHouseSystemInfo
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
#ifdef __SWE_GLIB_BUILDING__
#ifndef __SWE_GLIB_GSWE_HOUSE_SYSTEM_INFO_PRIVATE_H__
#define __SWE_GLIB_GSWE_HOUSE_SYSTEM_INFO_PRIVATE_H__

#include "gswe-types.h"

#include "gswe-house-system-info.h"

struct _GsweHouseSystemInfo {
    /* the house system's ID */
    GsweHouseSystem house_system;

    /* the character value that represents this house system in the Swiss Ephemeris library */
    gchar sweph_id;

    /* the name of this house system */
    gchar *name;

    /* reference count */
    guint refcount;
};

#endif /* __SWE_GLIB_GSWE_HOUSE_SYSTEM_INFO_PRIVATE_H__ */
#else /* not defined __SWE_GLIB_BUILDING__ */
#error __FILE__ "Can not be included, unless building SWE-GLib"
#endif /* __SWE_GLIB_BUILDING__ */

