/*
 * Copyright (C) 2013  Gergely Polonkai
 *
 * SWE-GLib is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your opinion)
 * any later version.
 *
 * SWE-GLib is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifdef __SWE_GLIB_BUILDING__
#ifndef __SWE_GLIB_PRIVATE_H__

#include "gswe-timestamp.h"

extern gchar *gswe_ephe_path;
extern GsweTimestamp *gswe_full_moon_base_date;

#endif /* __SWE_GLIB_PRIVATE_H__ */
#else /* not defined __SWE_GLIB_BUILDING__ */
#error __FILE__ "Can not be included, unless building SWE-GLib"
#endif /* __SWE_GLIB_BUILDING__ */

