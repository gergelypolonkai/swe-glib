/* gswe-planet-info.h: Planet related information
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
#ifndef __SWE_GLIB_GSWE_PLANET_INFO_H__
#define __SWE_GLIB_GSWE_PLANET_INFO_H__

#include <glib-object.h>

#include "gswe-types.h"

G_BEGIN_DECLS

/**
 * GswePlanetInfo:
 *
 * <structname>GswePlanetInfo</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 1.1
 */
typedef struct _GswePlanetInfo GswePlanetInfo;

GType gswe_planet_info_get_type(void);
#define GSWE_TYPE_PLANET_INFO (gswe_planet_info_get_type())

GswePlanetInfo *gswe_planet_info_new(void);

GswePlanetInfo *gswe_planet_info_ref(GswePlanetInfo *planet_info);

void gswe_planet_info_unref(GswePlanetInfo *planet_info);

void gswe_planet_info_set_planet(
        GswePlanetInfo *planet_info,
        GswePlanet planet);

GswePlanet gswe_planet_info_get_planet(GswePlanetInfo *planet_info);

void gswe_planet_info_set_sweph_id(
        GswePlanetInfo *planet_info,
        gint32 sweph_id);

gint32 gswe_planet_info_get_sweph_id(GswePlanetInfo *planet_info);

void gswe_planet_info_set_real_body(
        GswePlanetInfo *planet_info,
        gboolean real_body);

gboolean gswe_planet_info_get_real_body(GswePlanetInfo *planet_info);

void gswe_planet_info_set_orb(GswePlanetInfo *planet_info, gdouble orb);

gdouble gswe_planet_info_get_orb(GswePlanetInfo *planet_info);

void gswe_planet_info_set_name(GswePlanetInfo *planet_info, const gchar *name);

const gchar *gswe_planet_info_get_name(GswePlanetInfo *planet_info);

void gswe_planet_info_set_points(GswePlanetInfo *planet_info, gint points);

gint gswe_planet_info_get_points(GswePlanetInfo *planet_info);

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_PLANET_INFO_PRIVATE_H__ */

