/* gswe-timestamp.h - Converter GObject between Gregorian calendar date and
 * Julian day
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
#ifndef __SWE_GLIB_GSWE_TIMESTAMP_H__
#define __SWE_GLIB_GSWE_TIMESTAMP_H__

#include <glib-object.h>

#define GSWE_TYPE_TIMESTAMP             (gswe_timestamp_get_type())
#define GSWE_TIMESTAMP(obj)             (G_TYPE_CHECK_INSTANCE_CAST( \
            (obj), \
            GSWE_TYPE_TIMESTAMP, \
            GsweTimestamp))
#define GSWE_IS_TIMESTAMP(obj)          (G_TYPE_CHECK_INSTANCE_TYPE( \
            (obj), \
            GSWE_TYPE_TIMESTAMP))
#define GSWE_TIMESTAMP_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST( \
            (klass), \
            GSWE_TYPE_TIMESTAMP, \
            GsweTimestampClass))
#define GSWE_IS_TIMESTAMP_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE( \
            (klass), \
            GSWE_TYPE_TIMESTAMP))
#define GSWE_TIMESTAMP_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), \
            GSWE_TYPE_TIMESTAMP, \
            GsweTimestampClass))

typedef struct _GsweTimestamp GsweTimestamp;
typedef struct _GsweTimestampClass GsweTimestampClass;
typedef struct _GsweTimestampPrivate GsweTimestampPrivate;

/**
 * GsweTimestamp:
 *
 * The GsweTimestamp object's instance definition.
 */
struct _GsweTimestamp {
    /* Parent instance structure */
    GObject parent_instance;

    /* Instance members */

    /*< private >*/
    GsweTimestampPrivate *priv;
};

/**
 * GsweTimestampClass:
 * @parent_class: the parent class structure (#GObjectClass)
 *
 * The GsweTimestamp object's class definition.
 */
struct _GsweTimestampClass {
    /* Parent class */
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

GType gswe_timestamp_get_type(void);

/* Method definitions */
GsweTimestamp *gswe_timestamp_new(void);

GsweTimestamp *gswe_timestamp_new_from_julian_day(gdouble julian_day);

GsweTimestamp * gswe_timestamp_new_from_gregorian_full(gint    year,
                                                       gint    month,
                                                       gint    day,
                                                       gint    hour,
                                                       gint    minute,
                                                       gint    second,
                                                       gint    microsecond,
                                                       gdouble time_zone_offset);

void gswe_timestamp_set_gregorian_full(GsweTimestamp *timestamp,
                                       gint          year,
                                       gint          month,
                                       gint          day,
                                       gint          hour,
                                       gint          minute,
                                       gint          second,
                                       gint          microsecond,
                                       gdouble       time_zone_offset,
                                       GError        **err);

void gswe_timestamp_set_instant_recalc(GsweTimestamp *timestamp,
                                       gboolean      instant_recalc,
                                       GError        **err);

gboolean gswe_timestamp_get_instant_recalc(GsweTimestamp *timestamp);

void gswe_timestamp_set_gregorian_year(GsweTimestamp *timestamp,
                                       gint          gregorian_year,
                                       GError        **err);

gint gswe_timestamp_get_gregorian_year(GsweTimestamp *timestamp, GError **err);

void gswe_timestamp_set_gregorian_month(GsweTimestamp *timestamp,
                                        gint          gregorian_month,
                                        GError        **err);

gint gswe_timestamp_get_gregorian_month(GsweTimestamp *timestamp, GError **err);

void gswe_timestamp_set_gregorian_day(GsweTimestamp *timestamp,
                                      gint          gregorian_day,
                                      GError        **err);

gint gswe_timestamp_get_gregorian_day(GsweTimestamp *timestamp, GError **err);

void gswe_timestamp_set_gregorian_hour(GsweTimestamp *timestamp,
                                       gint          gregorian_hour,
                                       GError        **err);

gint gswe_timestamp_get_gregorian_hour(GsweTimestamp *timestamp, GError **err);

void gswe_timestamp_set_gregorian_minute(GsweTimestamp *timestamp,
                                         gint          gregorian_minute,
                                         GError        **err);

gint gswe_timestamp_get_gregorian_minute(GsweTimestamp *timestamp,
                                         GError        **err);

void gswe_timestamp_set_gregorian_second(GsweTimestamp *timestamp,
                                         gint          gregorian_second,
                                         GError        **err);

gint gswe_timestamp_get_gregorian_second(GsweTimestamp *timestamp,
                                         GError        **err);

void gswe_timestamp_set_gregorian_microsecond(GsweTimestamp *timestamp,
                                              gint          gregorian_microsecond,
                                              GError        **err);

gint gswe_timestamp_get_gregorian_microsecond(GsweTimestamp *timestamp,
                                              GError        **err);

void gswe_timestamp_set_gregorian_timezone(GsweTimestamp *timestamp,
                                           gdouble       gregorian_timezone_offset,
                                           GError        **err);

gdouble gswe_timestamp_get_gregorian_timezone(GsweTimestamp *timestamp);

#ifndef GSWE_DISABLE_DEPRECATED
G_DEPRECATED_FOR(gswe_timestamp_set_julian_day_et)
void gswe_timestamp_set_julian_day(GsweTimestamp *timestamp,
                                   gdouble       julian_day);

G_DEPRECATED_FOR(gswe_timestamp_get_julian_day_et)
gdouble gswe_timestamp_get_julian_day(GsweTimestamp *timestamp,
                                      GError        **err);
#endif

void gswe_timestamp_set_julian_day_et(GsweTimestamp *timestamp,
                                      gdouble       julian_day,
                                      GError        **err);

gdouble gswe_timestamp_get_julian_day_et(GsweTimestamp *timestamp,
                                         GError        **err);

void gswe_timestamp_set_julian_day_ut(GsweTimestamp *timestamp,
                                      gdouble       julian_day,
                                      GError        **err);

gdouble gswe_timestamp_get_julian_day_ut(GsweTimestamp *timestamp,
                                         GError        **err);

gdouble gswe_timestamp_get_sidereal_time(GsweTimestamp *timestamp,
                                         GError        **err);

#endif /* __SWE_GLIB_GSWE_TIMESTAMP_H__ */

