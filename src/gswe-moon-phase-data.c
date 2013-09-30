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

G_DEFINE_BOXED_TYPE(GsweMoonPhaseData, gswe_moon_phase_data, (GBoxedCopyFunc)gswe_moon_phase_data_ref, (GBoxedFreeFunc)gswe_moon_phase_data_unref);

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
 * Decreases reference count on @moon_phase_data by one. If reference count drops to zero, @moon_phase_data is freed.
 */
void
gswe_moon_phase_data_unref(GsweMoonPhaseData *moon_phase_data)
{
    if (--moon_phase_data->refcount == 0) {
        g_free(moon_phase_data);
    }
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
    if (moon_phase_data) {
        return moon_phase_data->phase;
    } else {
        return GSWE_MOON_PHASE_NONE;
    }
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
    if (moon_phase_data) {
        return moon_phase_data->illumination;
    } else {
        return 0.0;
    }
}

