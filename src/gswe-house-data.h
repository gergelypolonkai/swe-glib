/* gswe-house-data.h: House related data
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
#ifndef __SWE_GLIB_GSWE_HOUSE_DATA_H__
#define __SWE_GLIB_GSWE_HOUSE_DATA_H__

#include <glib-object.h>

#include "gswe-sign-info.h"

G_BEGIN_DECLS

/**
 * GsweHouseData:
 *
 * <structname>GsweHouseData</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 1.1
 */
typedef struct _GsweHouseData GsweHouseData;

GType gswe_house_data_get_type(void);
#define GSWE_TYPE_HOUSE_DATA (gswe_house_data_get_type())

guint gswe_house_data_get_house(GsweHouseData *house_data);
gdouble gswe_house_data_get_cusp_position(GsweHouseData *house_data);
GsweSignInfo *gswe_house_data_get_sign(GsweHouseData *house_data);

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_HOUSE_DATA_H__ */

