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
#include "gswe-moon-phase-data.h"
#include "gswe-sign-info.h"
#include "gswe-planet-info.h"
#include "gswe-planet-data.h"
#include "gswe-aspect-info.h"
#include "gswe-aspect-data.h"
#include "gswe-antiscion-axis-info.h"
#include "gswe-antiscion-data.h"
#include "gswe-house-system-info.h"
#include "gswe-house-data.h"
#include "gswe-timestamp.h"
#include "gswe-moment.h"
#include "gswe-enumtypes.h"

typedef enum {
    GSWE_ERROR_SUCCESS,
    GSWE_ERROR_SWE_NONFATAL,
    GSWE_ERROR_SWE_FATAL,
    GSWE_ERROR_INVALID_DATE,
    GSWE_ERROR_INVALID_TIME,
    GSWE_ERROR_NO_VALID_VALUE,
    GSWE_ERROR_UNKNOWN_HSYS,
    GSWE_ERROR_UNKNOWN_SIGN,
    GSWE_ERROR_UNKNOWN_PLANET,
    GSWE_ERROR_UNKNOWN_ANTISCION_AXIS,
    GSWE_ERROR_UNKNOWN_ASPECT,
} GsweError;

#define GSWE_ERROR gswe_error_quark()
GQuark gswe_error_quark(void);

void gswe_init();

GswePlanetInfo *gswe_find_planet_info_by_id(GswePlanet planet, GError **err);

GsweSignInfo *gswe_find_sign_info_by_id(GsweZodiac sign, GError **err);

GsweHouseSystemInfo *gswe_find_house_system_info_by_id(
        GsweHouseSystem house_system,
        GError **err);

GsweAspectInfo *gswe_find_aspect_info_by_id(GsweAspect aspect, GError **err);

GsweAntiscionAxisInfo *gswe_find_antiscion_axis_info_by_id(
        GsweAntiscionAxis antiscion_axis,
        GError **err);

GList *gswe_all_house_systems(void);

GList *gswe_all_planets(void);

GList *gswe_all_aspects(void);

GList *gswe_all_antiscion_axes(void);

#endif /* __SWE_GLIB_H__ */
