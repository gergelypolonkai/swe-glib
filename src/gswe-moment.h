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

/*
 * GsweMomentError:
 *
 * Error values for GsweTimestamp initialization
 */
//typedef enum {
//} GsweMomentError;

/**
 * GsweCoordinates:
 * @longitude: longitude part of the coordinates
 * @latitude: latitude part of the coordinates
 * @altitude: altitude relative to sea level
 *
 * GsweCoordinates specifies an exact point on Earth's surface
 */
typedef struct _GsweCoordinates {
    gdouble longitude;
    gdouble latitude;
    gdouble altitude;
} GsweCoordinates;

/**
 * GswePlanetData:
 * @planet_id: A GswePlanet, the identifier of the planet
 * @planet_info: A GswePlanetInfo structure, holding every information about the planet
 * @position: The longitude position of the planet
 * @retrograde: TRUE if the planet is in retrograde motion
 * @house: Number of the house in which the planet is in
 * @sign: A GsweSignInfo structure, holding every information about the sign the planet is in
 * @revision: An internal version number of the calculation
 */
typedef struct {
    GswePlanet planet_id;
    GswePlanetInfo *planet_info;
    gdouble position;
    gboolean retrograde;
    gint house;
    GsweSignInfo *sign;
    guint revision;
} GswePlanetData;

/**
 * GsweHouseData:
 * @house: the number of the house (usually in the range [1;12]. Sometimes may
 *         be [1;36].
 * @cusp_position: the position of the house's cusp on the sky
 * @sign: the #GsweSignInfo structure associated with the sign in which the
 *        house cusp is in
 */
typedef struct {
    guint house;
    gdouble cusp_position;
    GsweSignInfo *sign;
} GsweHouseData;

/**
 * GsweMoonPhaseData:
 * @phase: the current phase of the Moon
 * @illumination: the portion of the Moon that is currently illuminated
 */
typedef struct {
    GsweMoonPhase phase;
    gdouble illumination;
} GsweMoonPhaseData;

/**
 * GsweAspectData:
 * @planet1: the first planet in the aspect
 * @planet2: the second planet in the aspect
 * @distance: the distance between the two planets, in degrees
 * @aspect: the aspect between the two planets
 * @aspect_info: the #GsweAspectInfo structure associated with the aspect
 * @difference: the difference in percent between an exact aspect and this
 *              given aspect
 */
typedef struct {
    GswePlanetData *planet1;
    GswePlanetData *planet2;
    gdouble distance;
    GsweAspect aspect;
    GsweAspectInfo *aspect_info;
    gdouble difference;
} GsweAspectData;

/**
 * GsweMirrorData:
 * @planet1: the first planet in the mirror
 * @planet2: the second planet in the mirror
 * @mirror: the mirror on which this mirrorpoint is
 * @mirror_info: the #GsweMirrorInfo structure associated with this mirror
 * @difference: the difference in degrees between an exact mirror and this
 *              given mirrorpoint
 */
typedef struct {
    GswePlanetData *planet1;
    GswePlanetData *planet2;
    GsweMirror mirror;
    GsweMirrorInfo *mirror_info;
    gdouble difference;
} GsweMirrorData;

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

    /* Class members */

    /*< private >*/
    void (*changed)(GsweMoment *moment);
};

/* used by GSWE_TYPE_MOMENT */
GType gswe_moment_get_type(void);

/* Method definitions */
GsweMoment *gswe_moment_new(void);
GsweMoment *gswe_moment_new_full(GsweTimestamp *timestamp, gdouble longitude, gdouble latitude, gdouble altitude, GsweHouseSystem house_system);
void gswe_moment_set_timestamp(GsweMoment *moment, GsweTimestamp *timestamp);
GList *gswe_moment_get_house_cusps(GsweMoment *moment);
gint gswe_moment_get_house(GsweMoment *moment, gdouble position);
gboolean gswe_moment_has_planet(GsweMoment *moment, GswePlanet planet);
void gswe_moment_add_planet(GsweMoment *moment, GswePlanet planet);
void gswe_moment_add_all_planets(GsweMoment *moment);
GList *gswe_moment_get_planets(GsweMoment *moment);
GswePlanetData *gswe_moment_get_planet(GsweMoment *moment, GswePlanet planet);
guint gswe_moment_get_element_points(GsweMoment *moment, GsweElement element);
guint gswe_moment_get_quality_points(GsweMoment *moment, GsweQuality quality);
GsweMoonPhaseData *gswe_moment_get_moon_phase(GsweMoment *moment);
GList *gswe_moment_get_all_aspects(GsweMoment *moment);
GList *gswe_moment_get_planet_aspects(GsweMoment *moment, GswePlanet planet);
GList *gswe_moment_get_all_mirrorpoints(GsweMoment *moment);
GList *gswe_moment_get_all_planet_mirrorpoints(GsweMoment *moment, GswePlanet planet);
GList *gswe_moment_get_mirror_mirrorpoints(GsweMoment *moment, GsweMirror mirror);
GList *gswe_moment_get_mirror_planet_mirrorpoints(GsweMoment *moment, GsweMirror mirror, GswePlanet planet);

GType gswe_moon_phase_data_get_type(void);
#define GSWE_TYPE_MOON_PHASE_DATA (gswe_moon_phase_data_get_type())

GType gswe_planet_data_get_type(void);
#define GSWE_TYPE_PLANET_DATA (gswe_planet_data_get_type());

#endif /* __GSWE_MOMENT_H__ */

