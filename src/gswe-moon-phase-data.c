/* gswe-moon-phase-data.c: Moon phase representation
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
#include <math.h>

#include "gswe-types.h"

#include "swe-glib-private.h"
#include "gswe-moon-phase-data.h"
#include "gswe-moon-phase-data-private.h"
#include "gswe-timestamp.h"

#define SYNODIC 29.53058867

/**
 * SECTION:gswe-moon-phase-data
 * @short_description: a structure representing the phase of the Moon
 * @title: GsweMoonPhaseData
 * @stability: Stable
 * @include: swe-glib.h
 * @see_also: #GsweMoonPhase
 *
 * #GsweMoonPhaseData is a structure that represents the actual phase of the
 * Moon, including its illumination percentage.
 */

G_DEFINE_BOXED_TYPE(
        GsweMoonPhaseData,
        gswe_moon_phase_data,
        (GBoxedCopyFunc)gswe_moon_phase_data_ref,
        (GBoxedFreeFunc)gswe_moon_phase_data_unref);

/**
 * gswe_moon_phase_data_new:
 *
 * Creates a new #GsweMoonPhaseData object with reference count set to 1.
 *
 * Returns: (transfer full): a new #GsweMoonPhaseData object
 */
GsweMoonPhaseData *
gswe_moon_phase_data_new(void)
{
    GsweMoonPhaseData *ret;

    ret = g_new0(GsweMoonPhaseData, 1);
    ret->refcount = 1;

    return ret;
}

/**
 * gswe_moon_phase_data_ref:
 * @moon_phase_data: (in): a #GsweMoonPhaseData
 *
 * Increases reference count on @moon_phase_data by one.
 *
 * Returns: (transfer none): the same #GsweMoonPhaseData
 */
GsweMoonPhaseData *
gswe_moon_phase_data_ref(GsweMoonPhaseData *moon_phase_data)
{
    moon_phase_data->refcount++;

    return moon_phase_data;
}

/**
 * gswe_moon_phase_data_unref:
 * @moon_phase_data: (in): a #GsweMoonPhaseData
 *
 * Decreases reference count on @moon_phase_data by one. If reference count
 * drops to zero, @moon_phase_data is freed.
 */
void
gswe_moon_phase_data_unref(GsweMoonPhaseData *moon_phase_data)
{
    if (moon_phase_data == NULL) {
        return;
    }

    if (--moon_phase_data->refcount == 0) {
        g_free(moon_phase_data);
    }
}

/**
 * gswe_moon_phase_data_calculate_by_jd:
 * @moon_phase_data: a #GsweMoonPhaseData
 * @jd: a Julian Day number, with hours as fractions
 * @err: a #GError
 *
 * Calculates the moon at a given time, specified by @jd.
 */
void
gswe_moon_phase_data_calculate_by_jd(
        GsweMoonPhaseData *moon_phase_data,
        gdouble jd,
        GError **err)
{
    gdouble jdb,
            phase_percent;

    jdb = gswe_timestamp_get_julian_day_et(gswe_full_moon_base_date, err);

    if ((err) && (*err)) {
        return;
    }

    if ((phase_percent = fmod(((jd - jdb) * 100) / SYNODIC, 100)) < 0) {
        phase_percent += 100.0;
    }

    if ((phase_percent < 0) || (phase_percent > 100)) {
        g_error("Error during Moon phase calculation!");
    }

    moon_phase_data->illumination = (50.0 - fabs(phase_percent - 50.0)) * 2;

    if (phase_percent == 0) {
        moon_phase_data->phase = GSWE_MOON_PHASE_NEW;
    } else if (phase_percent < 25) {
        moon_phase_data->phase = GSWE_MOON_PHASE_WAXING_CRESCENT;
    } else if (phase_percent == 25) {
        moon_phase_data->phase = GSWE_MOON_PHASE_WAXING_HALF;
    } else if (phase_percent < 50) {
        moon_phase_data->phase = GSWE_MOON_PHASE_WAXING_GIBBOUS;
    } else if (phase_percent == 50) {
        moon_phase_data->phase = GSWE_MOON_PHASE_FULL;
    } else if (phase_percent < 75) {
        moon_phase_data->phase = GSWE_MOON_PHASE_WANING_GIBBOUS;
    } else if (phase_percent == 75) {
        moon_phase_data->phase = GSWE_MOON_PHASE_WANING_HALF;
    } else if (phase_percent < 100) {
        moon_phase_data->phase = GSWE_MOON_PHASE_WANING_CRESCENT;
    } else {
        moon_phase_data->phase = GSWE_MOON_PHASE_DARK;
    }
}

/**
 * gswe_moon_phase_data_calculate_by_timestamp:
 * @moon_phase_data: a #GsweMoonPhaseData
 * @timestamp: a #GsweTimestamp with a valid timestamp set
 * @err: a #GError
 *
 * Calculates the moon at a given time, specified by @timestamp.
 */
void
gswe_moon_phase_data_calculate_by_timestamp(
        GsweMoonPhaseData *moon_phase_data,
        GsweTimestamp *timestamp,
        GError **err)
{
    gdouble jd;

    jd = gswe_timestamp_get_julian_day_et(timestamp, err);

    if (err && *err) {
        return;
    }

    gswe_moon_phase_data_calculate_by_jd(moon_phase_data, jd, err);
}

/**
 * gswe_moon_phase_data_get_phase:
 * @moon_phase_data: (in): a GsweMoonPhaseData
 *
 * Gets the phase of the Moon in the given GsweMoonPhaseData.
 *
 * Returns: the Moon phase
 */
GsweMoonPhase
gswe_moon_phase_data_get_phase(GsweMoonPhaseData *moon_phase_data)
{
    return moon_phase_data->phase;
}

/**
 * gswe_moon_phase_data_get_illumination:
 * @moon_phase_data: (in): a GsweMoonPhaseData
 *
 * Gets the illumination percentage from the given GsweMoonPhaseData.
 *
 * Returns: the illumination percentage
 */
gdouble
gswe_moon_phase_data_get_illumination(GsweMoonPhaseData *moon_phase_data)
{
    return moon_phase_data->illumination;
}

