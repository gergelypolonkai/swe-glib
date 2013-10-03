/* gswe-moon-phase-data.h: Moon phase representation
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
#ifndef __SWE_GLIB_GSWE_MOON_PHASE_DATA_H__
#define __SWE_GLIB_GSWE_MOON_PHASE_DATA_H__

#include <glib-object.h>

#include "gswe-types.h"

G_BEGIN_DECLS

/**
 * GsweMoonPhaseData:
 *
 * <structname>GsweMoonPhaseData</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 1.1
 */
typedef struct _GsweMoonPhaseData GsweMoonPhaseData;

GsweMoonPhaseData *gswe_moon_phase_data_new(void);

GsweMoonPhaseData *gswe_moon_phase_data_ref(GsweMoonPhaseData *moon_phase_data);
void gswe_moon_phase_data_unref(GsweMoonPhaseData *moon_phase_data);

void gswe_moon_phase_data_calculate_by_jd(GsweMoonPhaseData *moon_phase_data, gdouble jd, GError **err);
void gswe_moon_phase_data_calculate_by_timestamp(GsweMoonPhaseData *moon_phase_data, GsweTimestamp *timestamp, GError **err);

GsweMoonPhase gswe_moon_phase_data_get_phase(GsweMoonPhaseData *moon_phase_data);
gdouble gswe_moon_phase_data_get_illumination(GsweMoonPhaseData *moon_phase_data);

GType gswe_moon_phase_data_get_type(void);
#define GSWE_TYPE_MOON_PHASE_DATA (gswe_moon_phase_data_get_type())

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_MOON_PHASE_DATA_H__ */

