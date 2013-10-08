/* gswe-antiscion-data.h: Antiscia related data
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
#ifndef __SWE_GLIB_GSWE_ANTISCION_DATA_H__
#define __SWE_GLIB_GSWE_ANTISCION_DATA_H__

#include <glib-object.h>

#include "gswe-planet-data.h"
#include "gswe-antiscion-axis-info.h"

G_BEGIN_DECLS

/**
 * GsweAntiscionData:
 *
 * <structname>GsweAntiscionData</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 1.1
 */
typedef struct _GsweAntiscionData GsweAntiscionData;

GType gswe_antiscion_data_get_type(void);
#define GSWE_TYPE_ANTISCION_DATA (gswe_antiscion_data_get_type())

GsweAntiscionData *gswe_antiscion_data_new(void);
GsweAntiscionData *gswe_antiscion_data_new_with_planets(GswePlanetData *planet1, GswePlanetData *planet2);

GsweAntiscionData *gswe_antiscion_data_ref(GsweAntiscionData *antiscion_data);
void gswe_antiscion_data_unref(GsweAntiscionData *antiscion_data);

void gswe_antiscion_data_calculate(GsweAntiscionData *antiscion_data);

void gswe_antiscion_data_set_planet1(GsweAntiscionData *antiscion_data, GswePlanetData *planet1);
GswePlanetData *gswe_antiscion_data_get_planet1(GsweAntiscionData *antiscion_data);

void gswe_antiscion_data_set_planet2(GsweAntiscionData *antiscion_data, GswePlanetData *planet2);
GswePlanetData *gswe_antiscion_data_get_planet2(GsweAntiscionData *antiscion_data);

GsweAntiscionAxis gswe_antiscion_data_get_axis(GsweAntiscionData *antiscion_data);
GsweAntiscionAxisInfo *gswe_antiscion_data_get_antiscion_axis_info(GsweAntiscionData *antiscion_data);
gdouble gswe_antiscion_data_get_difference(GsweAntiscionData *antiscion_data);

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_ANTISCION_DATA_H__ */

