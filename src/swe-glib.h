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

/**
 * GsweError:
 * @GSWE_ERROR_SUCCESS: No error
 * @GSWE_ERROR_SWE_NONFATAL: Non-fatal Swiss Ephemeris library error
 * @GSWE_ERROR_SWE_FATAL: Fatal Swiss Ephemeris library error
 * @GSWE_ERROR_INVALID_DATE: The specified Gregorian date is invalid
 * @GSWE_ERROR_INVALID_TIME: The specified time is invalid
 * @GSWE_ERROR_NO_VALID_VALUE: the #GsweTimestamp object holds no valid values
 * @GSWE_ERROR_UNKNOWN_HSYS: the requested house system is unknown
 * @GSWE_ERROR_UNKNOWN_SIGN: an invalid zodiac sign would have been returned
 * @GSWE_ERROR_NONADDED_PLANET: the referenced planet was not added with
 *                              gswe_moment_add_planet()
 *
 * Error codes returned by the SWE-GLib functions.
 */
typedef enum {
    GSWE_ERROR_SUCCESS,
    GSWE_ERROR_SWE_NONFATAL,
    GSWE_ERROR_SWE_FATAL,
    GSWE_ERROR_INVALID_DATE,
    GSWE_ERROR_INVALID_TIME,
    GSWE_ERROR_NO_VALID_VALUE,
    GSWE_ERROR_UNKNOWN_HSYS,
    GSWE_ERROR_UNKNOWN_SIGN,
    GSWE_ERROR_NONADDED_PLANET,
} GsweError;

/**
 * GSWE_ERROR:
 *
 * Error domain for SWE-GLib in general. Since 2.0, all errors generated by
 * SWE-GLib functions are from this domain. See #GError for more information on
 * error domains.
 */
#define GSWE_ERROR gswe_error_quark()
GQuark gswe_error_quark(void);

void gswe_init();

#endif /* __SWE_GLIB_H__ */

