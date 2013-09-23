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

GsweAntiscionAxis gswe_antiscion_axis_info_get_axis(GsweAntiscionAxisInfo *antiscion_axis_info);
GsweSignInfo *gswe_antiscion_axis_info_get_start_sign(GsweAntiscionAxisInfo *antiscion_axis_info);
const gchar *gswe_antiscion_axis_info_get_name(GsweAntiscionAxisInfo *antiscion_axis_info);
gboolean gswe_antiscion_axis_info_get_sign_offset(GsweAntiscionAxisInfo *antiscion_axis_info);

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_ANTISCION_AXIS_INFO_H__ */

