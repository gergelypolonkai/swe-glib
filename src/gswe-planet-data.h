/* gswe-planet-data.h: Planetary positions
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
#ifndef __SWE_GLIB_GSWE_PLANET_DATA_H__
#define __SWE_GLIB_GSWE_PLANET_DATA_H__

#include <glib-object.h>

#include "gswe-types.h"
#include "gswe-planet-info.h"

G_BEGIN_DECLS

/**
 * GswePlanetData:
 *
 * <structname>GswePlanetData</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 1.1
 */
typedef struct _GswePlanetData GswePlanetData;

GType gswe_planet_data_get_type(void);
#define GSWE_TYPE_PLANET_DATA (gswe_planet_data_get_type())

GswePlanet gswe_planet_data_get_planet(GswePlanetData *planet_data);
GswePlanetInfo *gswe_planet_data_get_planet_info(GswePlanetData *planet_data);
gdouble gswe_planet_data_get_position(GswePlanetData *planet_data);
gboolean gswe_planet_data_get_retrograde(GswePlanetData *planet_data);
gint gswe_planet_data_get_house(GswePlanetData *planet_data);
GsweSignInfo *gswe_planet_data_get_sign(GswePlanetData *planet_data);

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_PLANET_DATA_H__ */

