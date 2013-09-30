/* gswe-aspect-data.h: Aspect related data
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
#ifndef __SWE_GLIB_GSWE_ASPECT_DATA_H__
#define __SWE_GLIB_GSWE_ASPECT_DATA_H__

#include <glib-object.h>

#include "gswe-types.h"
#include "gswe-aspect-info.h"
#include "gswe-planet-data.h"

G_BEGIN_DECLS

/**
 * GsweAspectData:
 *
 * <structname>GsweAspectData</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 1.1
 */
typedef struct _GsweAspectData GsweAspectData;

GType gswe_aspect_data_get_type(void);
#define GSWE_TYPE_ASPECT_DATA (gswe_aspect_data_get_type())

GsweAspectData *gswe_aspect_data_new(void);
GsweAspectData *gswe_aspect_data_new_with_planets(GswePlanetData *planet1, GswePlanetData *planet2);

GsweAspectData *gswe_aspect_data_ref(GsweAspectData *aspect_data);
void gswe_aspect_data_unref(GsweAspectData *aspect_data);

void gswe_aspect_data_set_planet1(GsweAspectData *aspect_data, GswePlanetData *planet1);
GswePlanetData *gswe_aspect_data_get_planet1(GsweAspectData *aspect_data);

void gswe_aspect_data_set_planet2(GsweAspectData *aspect_data, GswePlanetData *planet2);
GswePlanetData *gswe_aspect_data_get_planet2(GsweAspectData *aspect_data);

gdouble gswe_aspect_data_get_distance(GsweAspectData *aspect_data);
GsweAspect gswe_aspect_data_get_aspect(GsweAspectData *aspect_data);
GsweAspectInfo *gswe_aspect_data_get_aspect_info(GsweAspectData *aspect_data);
gdouble gswe_aspect_data_get_difference(GsweAspectData *aspect_data);

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_ASPECT_DATA_H__ */

