/* gswe-planet-data-private.h: Private parts of GswePlanetData
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
#ifndef __SWE_GLIB_GSWE_PLANET_DATA_PRIVATE_H__
#define __SWE_GLIB_GSWE_PLANET_DATA_PRIVATE_H__

#include "gswe-planet-data.h"
#include "gswe-planet-info.h"

struct _GswePlanetData {
    /* A GswePlanetInfo structure, holding every information about the planet */
    GswePlanetInfo *planet_info;

    /* The longitude position of the planet */
    gdouble position;

    /* TRUE if the planet is in retrograde motion */
    gboolean retrograde;

    /* Number of the house in which the planet is in */
    gint house;

    /* A GsweSignInfo structure, holding every information about the sign the planet is in */
    GsweSignInfo *sign_info;

    /* An internal version number of the calculation */
    guint revision;

    /* reference count */
    guint refcount;
};

#endif /* __SWE_GLIB_GSWE_PLANET_DATA_PRIVATE_H__ */
#else /* not defined __SWE_GLIB_BUILDING__ */
#error __FILE__ "Can not be included, unless building SWE-GLib"
#endif /* __SWE_GLIB_BUILDING__ */

