/* gswe-aspect-info.h: Aspect related information
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
#ifndef __SWE_GLIB_GSWE_ASPECT_INFO_H__
#define __SWE_GLIB_GSWE_ASPECT_INFO_H__

#include <glib-object.h>

#include "gswe-types.h"

G_BEGIN_DECLS

/**
 * GsweAspectInfo:
 *
 * <structname>GsweAspectInfo</structname> is an opaque structure whose members
 * cannot be accessed directly.
 *
 * Since: 1.1
 */
typedef struct _GsweAspectInfo GsweAspectInfo;

GType gswe_aspect_info_get_type(void);
#define GSWE_TYPE_ASPECT_INFO (gswe_aspect_info_get_type())

GsweAspect gswe_aspect_info_get_aspect(GsweAspectInfo *aspect_info);
const gchar *gswe_aspect_info_get_name(GsweAspectInfo *aspect_info);
gdouble gswe_aspect_info_get_size(GsweAspectInfo *aspect_info);
gdouble gswe_aspect_info_get_orb_modifier(GsweAspectInfo *aspect_info);
gboolean gswe_aspect_info_get_harmonic(GsweAspectInfo *aspect_info);
gboolean gswe_aspect_info_get_major(GsweAspectInfo *aspect_info);

G_END_DECLS

#endif /* __SWE_GLIB_GSWE_ASPECT_INFO_H__ */

