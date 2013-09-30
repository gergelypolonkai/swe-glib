/* gswe-moon-phase-data-private.h: Private parts of GsweMoonPhaseData
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
#ifndef __SWE_GLIB_GSWE_MOON_PHASE_DATA_PRIVATE_H__
#define __SWE_GLIB_GSWE_MOON_PHASE_DATA_PRIVATE_H__

#include "gswe-moon-phase-data.h"
#include "gswe-types.h"

struct _GsweMoonPhaseData {
    /* the actual phase of the Moon */
    GsweMoonPhase phase;

    /* the illumination percentage of the Moon */
    gdouble illumination;

    /* reference count */
    guint refcount;
};

#endif /* __SWE_GLIB_GSWE_MOON_PHASE_DATA_PRIVATE_H__ */
#else /* not defined __SWE_GLIB_BUILDING__ */
#error __FILE__ "Can not be included, unless building SWE-GLib"
#endif /* __SWE_GLIB_BUILDING__ */

