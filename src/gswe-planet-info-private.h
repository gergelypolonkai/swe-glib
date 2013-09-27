/* gswe-planet-info-private.h: Private parts of GswePlanetInfo
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
#ifndef __SWE_GLIB_GSWE_PLANET_INFO_PRIVATE_H__
#define __SWE_GLIB_GSWE_PLANET_INFO_PRIVATE_H__

#include "gswe-types.h"
#include "gswe-planet-info.h"

struct _GswePlanetInfo {
    /* the planet ID */
    GswePlanet planet;

    /* the planet ID according to the Swiss Ephemeris libarary (or -1, if the planet has no such ID) */
    gint32 sweph_id;

    /* TRUE if the planet is a "real" celestial body on the sky. Please note that this will be true for Dark Moon (Lilith). Everything that has a planet ID in Swiss Ephemeris is treated as a real celestial body. */
    gboolean real_body;

    /* the planet's “personal” orb */
    gdouble orb;

    /* the planet's name */
    gchar *name;

    /* the value this planet counts in the element/quality points table */
    gint points;

    /* reference counter */
    guint refcount;
};

#endif /* __SWE_GLIB_GSWE_PLANET_INFO_PRIVATE_H__ */
#else /* not defined __SWE_GLIB_BUILDING__ */
#error __FILE__ "Can not be included, unless building SWE-GLib"
#endif /* __SWE_GLIB_BUILDING__ */

