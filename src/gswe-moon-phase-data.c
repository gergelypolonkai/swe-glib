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
#include "gswe-types.h"

#include "gswe-moon-phase-data.h"
#include "gswe-moon-phase-data-private.h"

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

G_DEFINE_BOXED_TYPE(GsweMoonPhaseData, gswe_moon_phase_data, (GBoxedCopyFunc)gswe_moon_phase_data_copy, (GBoxedFreeFunc)g_free);

GsweMoonPhaseData *
gswe_moon_phase_data_copy(GsweMoonPhaseData *moon_phase_data)
{
    GsweMoonPhaseData *ret = g_new0(struct _GsweMoonPhaseData, 1);

    ret->phase = moon_phase_data->phase;
    ret->illumination = moon_phase_data->illumination;

    return ret;
}

/**
 * gswe_moon_phase_data_set_phase:
 * @moon_phase_data: a GsweMoonPhaseData
 * @phase: the phase to set
 *
 * Sets the phase of the Moon in the given GsweMoonPhaseData.
 */
void
gswe_moon_phase_data_set_phase(GsweMoonPhaseData *moon_phase_data, GsweMoonPhase phase)
{
    if (moon_phase_data) {
        moon_phase_data->phase = phase;
    }
}

/**
 * gswe_moon_phase_data_get_phase:
 * @moon_phase_data: a GsweMoonPhaseData
 *
 * Gets the phase of the Moon in the given GsweMoonPhaseData.
 *
 * Returns: the Moon phase
 */
GsweMoonPhase
gswe_moon_phase_data_get_phase(GsweMoonPhaseData *moon_phase_data)
{
    if (moon_phase_data) {
        return moon_phase_data->phase;
    } else {
        return GSWE_MOON_PHASE_NONE;
    }
}

/**
 * gswe_moon_phase_data_set_illumination:
 * @moon_phase_data: a GsweMoonPhaseData
 * @illumination: the illumination to set
 *
 * Sets the illumination percentage in the given GsweMoonPhaseData.
 */
void
gswe_moon_phase_data_set_illumination(GsweMoonPhaseData *moon_phase_data, gdouble illumination)
{
    if (moon_phase_data) {
        moon_phase_data->illumination = illumination;
    }
}

/**
 * gswe_moon_phase_data_get_illumination:
 * @moon_phase_data: a GsweMoonPhaseData
 *
 * Gets the illumination percentage from the given GsweMoonPhaseData.
 *
 * Returns: the illumination percentage
 */
gdouble
gswe_moon_phase_data_get_illumination(GsweMoonPhaseData *moon_phase_data)
{
    if (moon_phase_data) {
        return moon_phase_data->illumination;
    } else {
        return 0.0;
    }
}

