/* SWE-GLib - GLib style wrapper library around Astrodienst's Swiss Ephemeris
 *
 * Copyright (C) 2013  Gergely Polonkai
 *
 * SWE-GLib is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your opinion)
 * any later version.
 *
 * SWE-GLib is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef __SWE_GLIB_H__
#define __SWE_GLIB_H__

#include <glib.h>
#include "gswe-types.h"
#include "gswe-timestamp.h"
#include "gswe-moment.h"
#include "gswe-enumtypes.h"

extern GHashTable *gswe_planet_info_table;
extern GHashTable *gswe_sign_info_table;
extern GHashTable *gswe_house_system_info_table;
extern GHashTable *gswe_aspect_info_table;
extern GHashTable *gswe_mirror_info_table;

void gswe_init();

#endif /* __SWE_GLIB_H__ */

