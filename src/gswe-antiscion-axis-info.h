/* gswe-antiscion-axis-info.h: Antiscion axis related information
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
#ifndef __SWE_GLIB_GSWE_ANTISCION_AXIS_INFO_H__
#define __SWE_GLIB_GSWE_ANTISCION_AXIS_INFO_H__

#include <glib-object.h>

#include "gswe-types.h"
#include "gswe-sign-info.h"

G_BEGIN_DECLS

/**
 * GsweAntiscionAxisInfo:
 *
 * <structname>GsweAntiscionAxisInfo</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 1.1
 */
typedef struct _GsweAntiscionAxisInfo GsweAntiscionAxisInfo;

GType gswe_antiscion_axis_info_get_type(void);
#define GSWE_TYPE_ANTISCION_AXIS_INFO (gswe_antiscion_axis_info_get_type())

GsweAntiscionAxisInfo *gswe_antiscion_axis_info_new(void);

GsweAntiscionAxisInfo *gswe_antiscion_axis_info_ref(GsweAntiscionAxisInfo *antiscion_axis_info);
void gswe_antiscion_axis_info_unref(GsweAntiscionAxisInfo *antiscion_axis_info);

void gswe_antiscion_axis_info_set_axis(GsweAntiscionAxisInfo *antiscion_axis_info, GsweAntiscionAxis axis);
GsweAntiscionAxis gswe_antiscion_axis_info_get_axis(GsweAntiscionAxisInfo *antiscion_axis_info);

void gswe_antiscion_axis_info_set_start_sign_info(GsweAntiscionAxisInfo *antiscion_axis_info, GsweSignInfo *sign_info);
GsweSignInfo *gswe_antiscion_axis_info_get_start_sign_info(GsweAntiscionAxisInfo *antiscion_axis_info);

void gswe_antiscion_axis_info_set_start_sign(GsweAntiscionAxisInfo *antiscion_axis_info, GsweZodiac sign, GError **err);
GsweZodiac gswe_antiscion_axis_info_get_start_sign(GsweAntiscionAxisInfo *antiscion_axis_info);

void gswe_antiscion_axis_info_set_name(GsweAntiscionAxisInfo *antiscion_axis_info, const gchar *name);
const gchar *gswe_antiscion_axis_info_get_name(GsweAntiscionAxisInfo *antiscion_axis_info);

void gswe_antiscion_axis_info_set_sign_offset(GsweAntiscionAxisInfo *antiscion_axis_info, gdouble sign_offset);
gdouble gswe_antiscion_axis_info_get_sign_offset(GsweAntiscionAxisInfo *antiscion_axis_info);

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_ANTISCION_AXIS_INFO_H__ */

