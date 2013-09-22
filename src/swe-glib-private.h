/*
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
#ifndef __SWE_GLIB_PRIVATE_H__

#include "gswe-timestamp.h"
#include "gswe-types.h"

extern gchar *gswe_ephe_path;
extern GsweTimestamp *gswe_full_moon_base_date;
extern GHashTable *gswe_planet_info_table;
extern GHashTable *gswe_sign_info_table;
extern GHashTable *gswe_house_system_info_table;
extern GHashTable *gswe_aspect_info_table;
extern GHashTable *gswe_antiscion_info_table;

GsweCoordinates *gswe_coordinates_copy(GsweCoordinates *coordinates);

#endif /* __SWE_GLIB_PRIVATE_H__ */
#else /* not defined __SWE_GLIB_BUILDING__ */
#error __FILE__ "Can not be included, unless building SWE-GLib"
#endif /* __SWE_GLIB_BUILDING__ */

