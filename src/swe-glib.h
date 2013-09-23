/* SWE-GLib - GLib style wrapper library around Astrodienst's Swiss Ephemeris
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
#ifndef __SWE_GLIB_H__
#define __SWE_GLIB_H__

#include <glib.h>
#include "gswe-types.h"
#include "gswe-aspect-data.h"
#include "gswe-timestamp.h"
#include "gswe-moment.h"
#include "gswe-enumtypes.h"

void gswe_init();

GType gswe_planet_info_get_type(void);
#define GSWE_TYPE_PLANET_INFO (gswe_planet_info_get_type())

GType gswe_sign_info_get_type(void);
#define GSWE_TYPE_SIGN_INFO (gswe_sign_info_get_type())

#endif /* __SWE_GLIB_H__ */

