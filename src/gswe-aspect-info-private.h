/* gswe-aspect-info-private.h: Private parts of GsweAspectInfo
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
#ifndef __SWE_GLIB_GSWE_ASPECT_INFO_PRIVATE_H__
#define __SWE_GLIB_GSWE_ASPECT_INFO_PRIVATE_H__

#include "gswe-types.h"
#include "gswe-aspect-info.h"

struct _GsweAspectInfo {
    /* the identifier of this aspect */
    GsweAspect aspect;

    /* the name of the aspect */
    gchar *name;

    /* the size of the aspect, in degrees */
    guint size;

    /* the modifier of the orb (the maximum allowable difference from an exact orb) */
    gdouble orb_modifier;

    /* shows whether this aspect is harmonic or not */
    gboolean harmonic;

    /* shows whether this aspect is major (Ptolemaic) or not */
    gboolean major;

    /** reference count */
    guint refcount;
};

#endif /* __SWE_GLIB_GSWE_ASPECT_INFO_PRIVATE_H__ */
#else /* not defined __SWE_GLIB_BUILDING__ */
#error __FILE__ "Can not be included, unless building SWE-GLib"
#endif /* __SWE_GLIB_BUILDING__ */

