/* gswe-antiscion-data-private.h: Private parts of GsweAntiscionData
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
#ifndef __SWE_GLIB_GSWE_ANTISCION_DATA_PRIVATE_H__
#define __SWE_GLIB_GSWE_ANTISCION_DATA_PRIVATE_H__

#include "gswe-planet-data.h"

#include "gswe-antiscion-data.h"

struct _GsweAntiscionData {
    /* the first planet in the antiscion */
    GswePlanetData *planet1;
    /* the second planet in the antiscion */
    GswePlanetData *planet2;
    /* the axis on which this antiscion is */
    GsweAntiscionAxis axis;
    /* the #GsweAntiscionAxisInfo structure associated with this antiscion */
    GsweAntiscionAxisInfo *antiscion_axis_info;
    /* the difference in degrees between an exact antiscion and this given antiscion */
    gdouble difference;
};

GsweAntiscionData *gswe_antiscion_data_copy(GsweAntiscionData *antiscion_data);

#endif /* __SWE_GLIB_GSWE_ANTISCION_DATA_PRIVATE_H__ */
#else /* not defined __SWE_GLIB_BUILDING__ */
#error __FILE__ "Can not be included, unless building SWE-GLib"
#endif /* __SWE_GLIB_BUILDING__ */

