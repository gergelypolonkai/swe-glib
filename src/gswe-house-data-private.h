/* gswe-house-data-private.h: Private parts of GsweHouseData
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
#ifndef __SWE_GLIB_GSWE_HOUSE_DATA_PRIVATE_H__
#define __SWE_GLIB_GSWE_HOUSE_DATA_PRIVATE_H__

#include "gswe-house-data.h"

struct _GsweHouseData {
    /* the number of the house (usually in the range [1;12]. Sometimes may be [1;36]) */
    guint house;

    /* the position of the house's cusp on the sky */
    gdouble cusp_position;

    /* the #GsweSignInfo structure associated with the sign in which the house cusp is in */
    GsweSignInfo *sign;
};

GsweHouseData *gswe_house_data_copy(GsweHouseData *house_data);

#endif /* __SWE_GLIB_GSWE_HOUSE_DATA_PRIVATE_H__ */
#else /* not defined __SWE_GLIB_BUILDING__ */
#error __FILE__ "Can not be included, unless building SWE-GLib"
#endif /* __SWE_GLIB_BUILDING__ */
