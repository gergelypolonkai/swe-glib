/* gswe-moment.h - Planetary moment object for SWE-GLib
 *
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
#ifndef __GSWE_MOMENT_H__
#define __GSWE_MOMENT_H__

#include <glib-object.h>

#include "gswe-timestamp.h"

#define GSWE_TYPE_MOMENT            (gswe_moment_get_type())
#define GSWE_MOMENT(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), GSWE_TYPE_MOMENT, GsweMoment))
#define GSWE_IS_MOMENT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), GSWE_TYPE_MOMENT))
#define GSWE_MOMENT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass), GSWE_TYPE_MOMENT, GsweMomentClass))
#define GSWE_IS_MOMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), GSWE_TYPE_MOMENT))
#define GSWE_MOMENT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), GSWE_TYPE_MOMENT, GsweMomentClass))

typedef struct _GsweMoment GsweMoment;
typedef struct _GsweMomentClass GsweMomentClass;
typedef struct _GsweMomentPrivate GsweMomentPrivate;

#define GSWE_MOMENT_ERROR gswe_moment_error_quark()
GQuark gswe_moment_error_quark(void);

/**
 * GsweMomentError:
 * @GSWE_MOMENT_ERROR_SUCCESS: no error
 * @GSWE_MOMENT_ERROR_UNKNOWN_HSYS: house system provided is unknown (a
 *                                  #GsweHouseSystem value must be passed)
 * @GSWE_MOMENT_ERROR_UNKNOWN_SIGN: an unknown zodiac sign is calculated
 * @GSWE_MOMENT_ERROR_NONADDED_PLANET: the referenced planet is not added to
 *                                     the GsweMoment object
 * @GSWE_MOMENT_ERROR_SWE_ERROR_NONFATAL: an error reported by the Swiss
 *                                        Ephemeris library. Errors marked with
 *                                        this value are not fatal, so it's
 *                                        more like a warning
 * @GSWE_MOMENT_ERROR_SWE_ERROR_FATAL: a fatal error reported by the Swiss
 *                                     Ephemeris library
 *
 * Error values for GsweTimestamp initialization
 */
typedef enum {
    GSWE_MOMENT_ERROR_SUCCESS,
    GSWE_MOMENT_ERROR_UNKNOWN_HSYS,
    GSWE_MOMENT_ERROR_UNKNOWN_SIGN,
    GSWE_MOMENT_ERROR_NONADDED_PLANET,
    GSWE_MOMENT_ERROR_SWE_ERROR_NONFATAL,
    GSWE_MOMENT_ERROR_SWE_ERROR_FATAL
} GsweMomentError;

struct _GsweMoment {
    /* Parent instance structure */
    GObject parent_instance;

    /* Instance members */

    /*< private >*/
    GsweMomentPrivate *priv;
};

/**
 * GsweMomentClass:
 * @parent_class: the parent class (#GObjectClass)
 */
struct _GsweMomentClass {
    /* Parent class structure */
    GObjectClass parent_class;

    /*< private >*/
    /* Padding for future expansion */
    void (*_swe_glib_reserved1)(void);
    void (*_swe_glib_reserved2)(void);
    void (*_swe_glib_reserved3)(void);
    void (*_swe_glib_reserved4)(void);
    void (*_swe_glib_reserved5)(void);
    void (*_swe_glib_reserved6)(void);
    void (*_swe_glib_reserved7)(void);
    void (*_swe_glib_reserved8)(void);
    void (*_swe_glib_reserved9)(void);
    void (*_swe_glib_reserved10)(void);
    void (*_swe_glib_reserved11)(void);
    void (*_swe_glib_reserved12)(void);
    void (*_swe_glib_reserved13)(void);
    void (*_swe_glib_reserved14)(void);
    void (*_swe_glib_reserved15)(void);
    void (*_swe_glib_reserved16)(void);
    void (*_swe_glib_reserved17)(void);
    void (*_swe_glib_reserved18)(void);
    void (*_swe_glib_reserved19)(void);
    void (*_swe_glib_reserved20)(void);
};

/* used by GSWE_TYPE_MOMENT */
GType gswe_moment_get_type(void);

/* Method definitions */
GsweMoment *gswe_moment_new(void);
GsweMoment *gswe_moment_new_full(GsweTimestamp *timestamp, gdouble longitude, gdouble latitude, gdouble altitude, GsweHouseSystem house_system);
void gswe_moment_set_timestamp(GsweMoment *moment, GsweTimestamp *timestamp);
GsweTimestamp *gswe_moment_get_timestamp(GsweMoment *moment);
void gswe_moment_set_coordinates(GsweMoment *moment, gdouble longitude, gdouble latitude, gdouble altitude);
GsweCoordinates *gswe_moment_get_coordinates(GsweMoment *moment);
void gswe_moment_set_house_system(GsweMoment *moment, GsweHouseSystem house_system);
GsweHouseSystem gswe_moment_get_house_system(GsweMoment *moment);
GList *gswe_moment_get_house_cusps(GsweMoment *moment, GError **err);
gint gswe_moment_get_house(GsweMoment *moment, gdouble position, GError **err);
gboolean gswe_moment_has_planet(GsweMoment *moment, GswePlanet planet);
void gswe_moment_add_planet(GsweMoment *moment, GswePlanet planet);
void gswe_moment_add_all_planets(GsweMoment *moment);
GList *gswe_moment_get_planets(GsweMoment *moment);
GswePlanetData *gswe_moment_get_planet(GsweMoment *moment, GswePlanet planet, GError **err);
guint gswe_moment_get_element_points(GsweMoment *moment, GsweElement element);
guint gswe_moment_get_quality_points(GsweMoment *moment, GsweQuality quality);
GsweMoonPhaseData *gswe_moment_get_moon_phase(GsweMoment *moment, GError **err);
GList *gswe_moment_get_all_aspects(GsweMoment *moment);
GList *gswe_moment_get_planet_aspects(GsweMoment *moment, GswePlanet planet, GError **err);
GList *gswe_moment_get_all_antiscia(GsweMoment *moment);
GList *gswe_moment_get_all_planet_antiscia(GsweMoment *moment, GswePlanet planet, GError **err);
GList *gswe_moment_get_axis_all_antiscia(GsweMoment *moment, GsweAntiscionAxis axis);
GList *gswe_moment_get_axis_planet_antiscia(GsweMoment *moment, GsweAntiscionAxis axis, GswePlanet planet, GError **err);

#endif /* __GSWE_MOMENT_H__ */

