/* gswe-moment.c - Planetary moment object for SWE-GLib
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
#include "swe-glib.h"
#include "gswe-types.h"
#include "gswe-moment.h"
#include "swe-glib-private.h"

#include "../swe/src/swephexp.h"

#define SYNODIC 29.53058867

#define GSWE_MOMENT_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), GSWE_TYPE_MOMENT, GsweMomentPrivate))

/**
 * GsweMomentPrivate:
 * @timestamp: a #GsweTimestmp object representing the current local time at
 *             the given position specified by @coordinates. Be warned though,
 *             that the time zone is NOT checked against the coordinates!
 * @coordinates: the coordinates of the observers position
 * @house_system: the house system this object uses
 * @revision: an internal counter which is incremented whenever the timestamp
 *            or the coordinates change. When this number changes, every data
 *            that has a *_revision value here will be recalculated before the
 *            data is served
 * @house_list: (element-type GsweHouseData): the list of house data
 * @house_revision: the revision of the calculated house data
 * @planet_list: (element-type GswePlanetData): the list of planets
 * @points_revision: the revision of the points
 * @element_points: the table of the element points
 * @quality_points: the table of the quality points
 * @moon_phase_revision: the revision of the Moon phase data
 * @moon_phase: the calculated Moon phase data
 * @aspect_list: (element-type GsweAspectData): the list of calculated aspects
 * @aspect_revision: the revision of the aspect data
 * @antiscia_list: (element-type GsweAntisciaData): the list of calculated
 *                    antiscia (mirror points)
 * @antiscia_revision: the revision of the antiscia data
 */
struct _GsweMomentPrivate {
    GsweTimestamp *timestamp;
    GsweCoordinates coordinates;
    GsweHouseSystem house_system;
    guint revision;
    GList *house_list;
    guint house_revision;
    GList *planet_list;
    guint points_revision;
    GHashTable *element_points;
    GHashTable *quality_points;
    guint moon_phase_revision;
    GsweMoonPhaseData moon_phase;
    GList *aspect_list;
    guint aspect_revision;
    GList *antiscia_list;
    guint antiscia_revision;
};

enum {
    SIGNAL_CHANGED,
    SIGNAL_LAST
};

enum {
    PROP_0,
    PROP_TIMESTAMP,
    PROP_COORDINATES,
    PROP_HOUSE_SYSTEM
};

struct GsweAspectFinder {
    GswePlanet planet1;
    GswePlanet planet2;
};

static guint gswe_moment_signals[SIGNAL_LAST] = {0};

static void gswe_moment_dispose(GObject *gobject);
static void gswe_moment_finalize(GObject *gobject);
static void gswe_moment_set_property(GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gswe_moment_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);

G_DEFINE_TYPE(GsweMoment, gswe_moment, G_TYPE_OBJECT);

static void
gswe_moment_class_init(GsweMomentClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

    g_type_class_add_private(klass, sizeof(GsweMomentPrivate));

    gobject_class->dispose = gswe_moment_dispose;
    gobject_class->finalize = gswe_moment_finalize;
    gobject_class->set_property = gswe_moment_set_property;
    gobject_class->get_property = gswe_moment_get_property;

    /**
     * GsweMoment::changed:
     * @moment: the GsweMoment object that received the signal
     *
     * The ::changed signal is emitted each time the time or coordinates are changed
     */
    gswe_moment_signals[SIGNAL_CHANGED] = g_signal_new("changed", G_OBJECT_CLASS_TYPE(gobject_class), G_SIGNAL_RUN_FIRST, 0, NULL, NULL, g_cclosure_marshal_generic, G_TYPE_NONE, 0);

    /**
     * GsweMoment:timestamp:
     *
     * The timestamp associated with this moment
     */
    g_object_class_install_property(gobject_class, PROP_TIMESTAMP, g_param_spec_object("timestamp", "Timestamp", "Timestamp of this moment", GSWE_TYPE_TIMESTAMP, G_PARAM_READWRITE));

    /**
     * GsweMoment:coordinates:
     *
     * The geographical coordinates associated with this moment
     */
    g_object_class_install_property(gobject_class, PROP_COORDINATES, g_param_spec_boxed("coordinates", "Coordinates", "Geographical coordinates", GSWE_TYPE_COORDINATES, G_PARAM_READWRITE));

    /**
     * GsweMoment:house-system:
     *
     * The house system associated with this moment
     */
    g_object_class_install_property(gobject_class, PROP_HOUSE_SYSTEM, g_param_spec_enum("house-system", "House System", "Astrological house system", GSWE_TYPE_HOUSE_SYSTEM, GSWE_HOUSE_SYSTEM_PLACIDUS, G_PARAM_READWRITE));
}

static void
gswe_moment_emit_changed(GsweMoment *moment)
{
    g_signal_emit(moment, gswe_moment_signals[SIGNAL_CHANGED], 0);
}

static void
gswe_moment_init(GsweMoment *moment)
{
    moment->priv = GSWE_MOMENT_GET_PRIVATE(moment);

    moment->priv->timestamp = NULL;
    moment->priv->house_list = NULL;
    moment->priv->planet_list = NULL;
    moment->priv->aspect_list = NULL;
    moment->priv->antiscia_list = NULL;
    moment->priv->element_points = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    moment->priv->quality_points = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    moment->priv->house_revision = 0;
    moment->priv->points_revision = 0;
    moment->priv->moon_phase_revision = 0;
    moment->priv->aspect_revision = 0;
    moment->priv->antiscia_revision = 0;
    moment->priv->revision = 1;
}

static void
gswe_moment_timestamp_changed(GsweTimestamp *timestamp, GsweMoment *moment)
{
    moment->priv->revision++;
    gswe_moment_emit_changed(moment);
}

static void
gswe_moment_dispose(GObject *gobject)
{
    GsweMoment *moment = GSWE_MOMENT(gobject);

    g_signal_handlers_disconnect_by_func(moment->priv->timestamp, gswe_moment_timestamp_changed, NULL);

    g_clear_object(&moment->priv->timestamp);

    G_OBJECT_CLASS(gswe_moment_parent_class)->dispose(gobject);
}

static void
gswe_moment_finalize(GObject *gobject)
{
    GsweMoment *moment = GSWE_MOMENT(gobject);

    g_list_free_full(moment->priv->house_list, g_free);
    g_list_free_full(moment->priv->planet_list, g_free);

    G_OBJECT_CLASS(gswe_moment_parent_class)->finalize(gobject);
}

static void
gswe_moment_set_property(GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
    GsweMoment *moment = GSWE_MOMENT(object);

    switch (prop_id) {
        case PROP_TIMESTAMP:
            gswe_moment_set_timestamp(moment, (g_value_get_object(value)));

            break;

        case PROP_COORDINATES:
            {
                GsweCoordinates *coords = g_value_get_boxed(value);

                gswe_moment_set_coordinates(moment, coords->longitude, coords->latitude, coords->altitude);
            }

            break;


        case PROP_HOUSE_SYSTEM:
            gswe_moment_set_house_system(moment, g_value_get_enum(value));

            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);

            break;
    }
}

static void
gswe_moment_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
    GsweMoment *moment = GSWE_MOMENT(object);
    GsweMomentPrivate *priv = moment->priv;

    switch (prop_id) {
        case PROP_TIMESTAMP:
            g_value_set_object(value, priv->timestamp);

            break;

        case PROP_COORDINATES:
            {
                GsweCoordinates *coords = gswe_coordinates_copy(&(priv->coordinates));
                g_value_set_boxed(value, coords);
            }

            break;

        case PROP_HOUSE_SYSTEM:
            g_value_set_enum(value, priv->house_system);

            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);

            break;
    }
}

/**
 * gswe_moment_set_timestamp:
 * @moment: A GsweMoment object
 * @timestamp: A GsweTimestamp object. The moment object holds a reference on
 *             timestamp, which is cleared when a new timestamp is set, or the
 *             moment object is disposed.
 *
 * Sets a new timestamp for this planetary moment. Also emits the ::changed
 * signal to notify owner of this change. This helps redrawing screen data
 * according to the new time value.
 */
void
gswe_moment_set_timestamp(GsweMoment *moment, GsweTimestamp *timestamp)
{
    if (moment->priv->timestamp != NULL) {
        g_signal_handlers_disconnect_by_func(moment->priv->timestamp, gswe_moment_timestamp_changed, NULL);
        g_clear_object(&moment->priv->timestamp);
    }

    moment->priv->revision++;
    moment->priv->timestamp = timestamp;
    g_object_ref(timestamp);
    g_signal_connect(G_OBJECT(timestamp), "changed", G_CALLBACK(gswe_moment_timestamp_changed), moment);

    /* Emit the changed signal to notify registrants of the change */
    gswe_moment_emit_changed(moment);
}

/**
 * gswe_moment_get_timestamp:
 * @moment: a GsweMoment object
 *
 * Gets the #GsweTimestamp object associated with @moment
 *
 * Returns: (transfer none): the GsweTimestamp object associated with @moment.
 * The returned object is used by @moment exclusively. If you need it even
 * after @moment is destroyed, call g_object_ref() on it.
 */
GsweTimestamp *
gswe_moment_get_timestamp(GsweMoment *moment)
{
    return moment->priv->timestamp;
}

/**
 * gswe_moment_set_coordinates:
 * @moment: a GsweMoment
 * @longitude: the longitude part of the coordinates, in degrees
 * @latitude: the latitude part of the coordinates, in degrees
 * @altitude: the altitude part of the coordinates, in meters. As also noted in
 *            the README, it is safe to pass a value of around 400.0, unless
 *            you want to create a *really* precise chart
 *
 * Sets the coordinates associated with @moment. Emits the ::changed signal on
 * @moment. All values depending on the coordinates (planetary and house cusp
 * positions, aspects, antiscion, so basically everything) should be
 * re-fetched after changing it.
 */
void
gswe_moment_set_coordinates(GsweMoment *moment, gdouble longitude, gdouble latitude, gdouble altitude)
{
    moment->priv->coordinates.longitude = longitude;
    moment->priv->coordinates.latitude = latitude;
    moment->priv->coordinates.altitude = altitude;
    moment->priv->revision++;
    gswe_moment_emit_changed(moment);
}

/**
 * gswe_moment_get_coordinates:
 * @moment: a GsweMoment
 *
 * Gets the coordinates associated with @moment.
 *
 * Returns: (transfer full): a newly allocated GsweCoordinates structure with
 *          the coordinates associated with @moment. The returned pointer
 *          should be freed with g_free if you don't need it any more.
 */
GsweCoordinates *
gswe_moment_get_coordinates(GsweMoment *moment)
{
    return gswe_coordinates_copy(&(moment->priv->coordinates));
}

/**
 * gswe_moment_set_house_system:
 * @moment: a GsweMoment object
 * @house_system: the new house system to associate with @moment
 *
 * Associates a new house system with @moment. Emits the ::changed signal.
 * House cusp positions are recalculated upon next fetch.
 */
void
gswe_moment_set_house_system(GsweMoment *moment, GsweHouseSystem house_system)
{
    moment->priv->house_system = house_system;
    moment->priv->revision++;
    gswe_moment_emit_changed(moment);
}

/**
 * gswe_moment_get_house_system:
 * @moment: a GsweMoment object
 *
 * Returns: The house system currently associated with @moment
 */
GsweHouseSystem
gswe_moment_get_house_system(GsweMoment *moment)
{
    return moment->priv->house_system;
}

/**
 * gswe_moment_error_quark:
 *
 * Returns the #GQuark that will be used for #GError values returned by the
 * SWE-GLib API.
 *
 * Returns: a GQuark used to identify errors coming from the SWE-GLib API
 */
GQuark
gswe_moment_error_quark(void)
{
    return g_quark_from_static_string("swe-glib-gswe-moment-error");
}

/**
 * gswe_moment_new:
 *
 * Creates a new, empty GsweMoment object. The object created this way can not
 * be used for any calculations yet, you need to call various gswe_moment_set_*
 * functions first. It is preferred to call gswe_moment_new_full() instead.
 *
 * Returns: a new GsweMoment object
 */
GsweMoment *
gswe_moment_new(void)
{
    return (GsweMoment *)g_object_new(GSWE_TYPE_MOMENT, NULL);
}

/**
 * gswe_moment_new_full:
 * @timestamp: a #GsweTimestamp, the exact time of your calculations
 * @longitude: the longitude part of the observer's position, in degrees
 * @latitude: the latitude part of the observer's position, in degrees
 * @altitude: the altitude part of the coordinates, in meters. As also noted in
 *            the README, it is safe to pass a value of around 400.0, unless
 *            you want to create a *really* precise chart
 * @house_system: the house system you want to use. WARNING! Using GSWE_HOUSE_SYSTEM_NONE is currently a bad idea, the results are unpredicted
 *
 * Creates a new GsweMoment object with the timestamp, coordinates and house system set. This is the preferred way to create a GsweMoment object.
 *
 * Returns: a new GsweMoment object, which is usable out of the box
 */
GsweMoment *
gswe_moment_new_full(GsweTimestamp *timestamp, gdouble longitude, gdouble latitude, gdouble altitude, GsweHouseSystem house_system)
{
    GsweMoment *moment = gswe_moment_new();

    moment->priv->timestamp = timestamp;
    g_object_ref(timestamp);
    g_signal_connect(G_OBJECT(timestamp), "changed", G_CALLBACK(gswe_moment_timestamp_changed), moment);
    moment->priv->coordinates.longitude = longitude;
    moment->priv->coordinates.latitude = latitude;
    moment->priv->coordinates.altitude = altitude;
    moment->priv->house_system = house_system;

    if (house_system == GSWE_HOUSE_SYSTEM_NONE) {
        g_warning("Using GSWE_HOUSE_SYSTEM_NONE is unsafe. You have been warned!");
    }

    return moment;
}

static gint
find_by_planet_id(gconstpointer a, gconstpointer b)
{
    const GswePlanetData *planet_data = a;
    const GswePlanet *planet = b;

    if (planet_data->planet_id == *planet) {
        return 0;
    }

    return 1;
}

static void
gswe_calculate_data_by_position(GsweMoment *moment, GswePlanet planet, gdouble position, GError **err)
{
    GswePlanetData *planet_data = (GswePlanetData *)(g_list_find_custom(moment->priv->planet_list, &planet, find_by_planet_id)->data);
    GsweZodiac sign;
    GsweSignInfo *sign_info;

    if (planet_data == NULL) {
        return;
    }

    if (planet_data->revision == moment->priv->revision) {
        return;
    }

    sign = (GsweZodiac)ceil(position / 30.0);

    if ((sign_info = g_hash_table_lookup(gswe_sign_info_table, GINT_TO_POINTER(sign))) == NULL) {
        g_error("Calculations brought an unknown sign!");
    }

    planet_data->position = position;
    planet_data->retrograde = FALSE;
    planet_data->house = gswe_moment_get_house(moment, position, err);
    planet_data->sign = sign_info;
    planet_data->revision = moment->priv->revision;
}

static void
gswe_moment_calculate_house_positions(GsweMoment *moment, GError **err)
{
    gdouble cusps[13],
            ascmc[10],
            jd;
    gint i;
    GsweHouseSystemInfo *house_system_data;

    if (moment->priv->house_revision == moment->priv->revision) {
        return;
    }

    if ((house_system_data = g_hash_table_lookup(gswe_house_system_info_table, GINT_TO_POINTER(moment->priv->house_system))) == NULL) {
        g_set_error(err, GSWE_MOMENT_ERROR, GSWE_MOMENT_ERROR_UNKNOWN_HSYS, "Unknown house system");

        return;
    }

    jd = gswe_timestamp_get_julian_day(moment->priv->timestamp, err);

    if ((err) && (*err)) {
        return;
    }

    swe_houses(jd, moment->priv->coordinates.latitude, moment->priv->coordinates.longitude, house_system_data->sweph_id, cusps, ascmc);

    g_list_free_full(moment->priv->house_list, g_free);
    moment->priv->house_list = NULL;

    /* TODO: SWE house system 'G' (Gauquelin sector cusps) have 36 houses; we
     * should detect that somehow (house system 'G' is not implemented yet in
     * GsweHouseSystem, and all other house systems have exactly 12 houses, so
     * this should not cause trouble yet, though) */
    for (i = 12; i >= 1; i--) {
        GsweHouseData *house_data = g_new0(GsweHouseData, 1);

        house_data->house = i;
        house_data->cusp_position = cusps[i];

        if ((house_data->sign = g_hash_table_lookup(gswe_sign_info_table, GINT_TO_POINTER((gint)ceilf(cusps[i] / 30.0)))) == NULL) {
            g_list_free_full(moment->priv->house_list, g_free);
            g_set_error(err, GSWE_MOMENT_ERROR, GSWE_MOMENT_ERROR_UNKNOWN_SIGN, "Calculation brought an unknown sign");

            return;
        }

        moment->priv->house_list = g_list_prepend(moment->priv->house_list, house_data);
    }

    moment->priv->house_revision = moment->priv->revision;

    if (gswe_moment_has_planet(moment, GSWE_PLANET_ASCENDENT)) {
        gswe_calculate_data_by_position(moment, GSWE_PLANET_ASCENDENT, ascmc[0], err);
    }

    if (gswe_moment_has_planet(moment, GSWE_PLANET_MC)) {
        gswe_calculate_data_by_position(moment, GSWE_PLANET_MC, ascmc[1], err);
    }

    if (gswe_moment_has_planet(moment, GSWE_PLANET_VERTEX)) {
        gswe_calculate_data_by_position(moment, GSWE_PLANET_VERTEX, ascmc[3], err);
    }
}

/**
 * gswe_moment_get_house_cusps:
 * @moment: The GsweMoment object to operate on
 * @err: a #GError
 *
 * Calculate house cusp positions based on the house system, location and time set in @moment.
 *
 * Returns: (element-type GsweHouseData) (transfer none): a GList of #GsweHouseData
 */
GList *
gswe_moment_get_house_cusps(GsweMoment *moment, GError **err)
{
    if (moment->priv->house_revision != moment->priv->revision) {
        gswe_moment_calculate_house_positions(moment, err);
    }

    return moment->priv->house_list;
}

/**
 * gswe_moment_has_planet:
 * @moment: a GsweMoment
 * @planet: the planet whose existence is queried
 *
 * Checks if @planet is added to @moment, e.g. its position and related data is calculated.
 *
 * Returns: #TRUE if @planet is already added to @moment, #FALSE otherwise
 */
gboolean
gswe_moment_has_planet(GsweMoment *moment, GswePlanet planet)
{
    return (g_list_find_custom(moment->priv->planet_list, &planet, find_by_planet_id) != NULL);
}

/**
 * gswe_moment_add_planet:
 * @moment: a GsweMoment object
 * @planet: the planet to add
 *
 * Adds @planet to the calculated planets of @moment.
 */
void
gswe_moment_add_planet(GsweMoment *moment, GswePlanet planet)
{
    GswePlanetData *planet_data = g_new0(GswePlanetData, 1);
    GswePlanetInfo *planet_info;

    if (gswe_moment_has_planet(moment, planet)) {
        return;
    }

    if ((planet_info = g_hash_table_lookup(gswe_planet_info_table, GINT_TO_POINTER(planet))) == NULL) {
        g_warning("Unknown planet ID: %d", planet);

        return;
    }

    planet_data->planet_id = planet;
    planet_data->planet_info = planet_info;
    planet_data->position = 0.0;
    planet_data->house = 1;
    planet_data->sign = NULL;
    planet_data->revision = 0;

    moment->priv->planet_list = g_list_append(moment->priv->planet_list, planet_data);
}

static void
planet_add(gpointer key, gpointer value, gpointer user_data)
{
    GswePlanet planet = (GswePlanet)GPOINTER_TO_INT(key);
    GsweMoment *moment = GSWE_MOMENT(user_data);

    gswe_moment_add_planet(moment, planet);
}

/**
 * gswe_moment_add_all_planets:
 * @moment: a GsweMoment object
 *
 * Adds all known planets to @moment.
 */
void
gswe_moment_add_all_planets(GsweMoment *moment)
{
    g_hash_table_foreach(gswe_planet_info_table, planet_add, moment);
}

static void
gswe_moment_calculate_planet(GsweMoment *moment, GswePlanet planet, GError **err)
{
    GswePlanetData *planet_data = (GswePlanetData *)(g_list_find_custom(moment->priv->planet_list, &planet, find_by_planet_id)->data);
    gchar serr[AS_MAXCH];
    gint ret;
    gdouble x2[6],
            jd;
    GError *calc_err = NULL;

    if (planet_data == NULL) {
        return;
    }

    if (planet_data->revision == moment->priv->revision) {
        return;
    }

    if (planet_data->planet_info->real_body == FALSE) {
        g_warning("The position data of planet %d can not be calculated by this function", planet);

        return;
    }

    swe_set_topo(moment->priv->coordinates.longitude, moment->priv->coordinates.latitude, moment->priv->coordinates.altitude);
    jd = gswe_timestamp_get_julian_day(moment->priv->timestamp, err);

    if ((err) && (*err)) {
        return;
    }

    if ((ret = swe_calc(jd, planet_data->planet_info->sweph_id, SEFLG_SPEED | SEFLG_TOPOCTR, x2, serr)) < 0) {
        g_set_error(err, GSWE_MOMENT_ERROR, GSWE_MOMENT_ERROR_SWE_ERROR_FATAL, "Swiss Ephemeris error: %s", serr);

        return;
    } else if (ret != (SEFLG_SPEED | SEFLG_TOPOCTR)) {
        g_set_error(err, GSWE_MOMENT_ERROR, GSWE_MOMENT_ERROR_SWE_ERROR_NONFATAL, "Swiss Ephemeris error: %s", serr);
    }

    gswe_calculate_data_by_position(moment, planet, x2[0], &calc_err);

    if (calc_err != NULL) {
        g_clear_error(err);

        if (err) {
            *err = calc_err;
        }
    }

    planet_data->retrograde = (x2[3] < 0);
}

static void
calculate_planet(GswePlanetData *planet_data, GsweMoment *moment)
{
    gswe_moment_calculate_planet(moment, planet_data->planet_id, NULL);
}

static void
gswe_moment_calculate_all_planets(GsweMoment *moment)
{
    g_list_foreach(moment->priv->planet_list, (GFunc)calculate_planet, moment);
}

/**
 * gswe_moment_get_planets:
 * @moment: The GsweMoment to operate on
 *
 * Get all the planets added to @moment.
 *
 * Returns: (element-type GswePlanetData) (transfer none): A #GList of #GswePlanetData.
 */
GList *
gswe_moment_get_planets(GsweMoment *moment)
{
    return moment->priv->planet_list;
}

/**
 * gswe_moment_get_house:
 * @moment: a GsweMoment object
 * @position: an ecliptic position
 * @err: a #GError
 *
 * Returns the number of the house in which @position is.
 *
 * Returns: the number of the house in which @position is. This function always yields 0 if the associated house system is #GSWE_HOUSE_SYSTEM_NONE.
 */
gint
gswe_moment_get_house(GsweMoment *moment, gdouble position, GError **err)
{
    gint i;

    if (moment->priv->house_system == GSWE_HOUSE_SYSTEM_NONE) {
        return 0;
    }

    gswe_moment_calculate_house_positions(moment, err);

    /* TODO: SWE house system 'G' (Gauquelin sector cusps) have 36 houses; we
     * should detect that somehow (house system 'G' is not implemented yet in
     * GsweHouseSystem, and all other house systems have exactly 12 houses, so
     * this should not cause trouble yet, though) */
    for (i = 1; i <= 12; i++) {
        gint j = (i < 12) ? i + 1 : 1;
        gdouble cusp_i = *(gdouble *)g_list_nth_data(moment->priv->house_list, i - 1),
                cusp_j = *(gdouble *)g_list_nth_data(moment->priv->house_list, j - 1);

        if (cusp_j < cusp_i) {
            if ((position >= cusp_i) || (position < cusp_j)) {
                return i;
            }
        } else {
            if ((position >= cusp_i) && (position < cusp_j)) {
                return i;
            }
        }
    }

    return 0;
}

GswePlanetData *
gswe_moment_get_planet(GsweMoment *moment, GswePlanet planet, GError **err)
{
    GswePlanetData *planet_data = (GswePlanetData *)(g_list_find_custom(moment->priv->planet_list, &planet, find_by_planet_id)->data);

    if (planet_data == NULL) {
        g_set_error(err, GSWE_MOMENT_ERROR, GSWE_MOMENT_ERROR_NONADDED_PLANET, "Specified planet is not added to the moment object");

        return NULL;
    }

    gswe_moment_calculate_planet(moment, planet, err);

    return planet_data;
}

static void
add_points(GswePlanetData *planet_data, GsweMoment *moment)
{
    guint point;

    gswe_moment_calculate_planet(moment, planet_data->planet_id, NULL);

    point = GPOINTER_TO_INT(g_hash_table_lookup(moment->priv->element_points, GINT_TO_POINTER(planet_data->sign->element))) + planet_data->planet_info->points;
    g_hash_table_replace(moment->priv->element_points, GINT_TO_POINTER(planet_data->sign->element), GINT_TO_POINTER(point));

    point = GPOINTER_TO_INT(g_hash_table_lookup(moment->priv->quality_points, GINT_TO_POINTER(planet_data->sign->quality)));

    point += planet_data->planet_info->points;
    g_hash_table_replace(moment->priv->quality_points, GINT_TO_POINTER(planet_data->sign->quality), GINT_TO_POINTER(point));
}

static void
gswe_moment_calculate_points(GsweMoment *moment)
{
    if (moment->priv->points_revision == moment->priv->revision) {
        return;
    }

    g_hash_table_remove_all(moment->priv->element_points);
    g_hash_table_remove_all(moment->priv->quality_points);

    g_list_foreach(moment->priv->planet_list, (GFunc)add_points, moment);

    moment->priv->points_revision = moment->priv->revision;
}

guint
gswe_moment_get_element_points(GsweMoment *moment, GsweElement element)
{
    guint point;

    gswe_moment_calculate_points(moment);

    point = GPOINTER_TO_INT(g_hash_table_lookup(moment->priv->element_points, GINT_TO_POINTER(element)));

    return point;
}

guint
gswe_moment_get_quality_points(GsweMoment *moment, GsweQuality quality)
{
    guint point;

    gswe_moment_calculate_points(moment);

    point = GPOINTER_TO_INT(g_hash_table_lookup(moment->priv->quality_points, GINT_TO_POINTER(quality)));

    return point;
}

GsweMoonPhaseData *
gswe_moment_get_moon_phase(GsweMoment *moment, GError **err)
{
    gdouble difference,
            phase_percent,
            jd,
            jdb;

    if (moment->priv->moon_phase_revision == moment->priv->revision) {
        return &(moment->priv->moon_phase);
    }

    jd = gswe_timestamp_get_julian_day(moment->priv->timestamp, err);

    if ((err) && (*err)) {
        return NULL;
    }

    jdb = gswe_timestamp_get_julian_day(gswe_full_moon_base_date, err);

    if ((err) && (*err)) {
        return NULL;
    }

    difference = (jd - jdb);
    phase_percent = fmod((difference * 100) / SYNODIC, 100);

    if (phase_percent < 0) {
        phase_percent += 100.0;
    }

    if ((phase_percent < 0) || (phase_percent > 100)) {
        g_error("Error during Moon phase calculation!");
    }

    moment->priv->moon_phase.illumination = (50.0 - fabs(phase_percent - 50.0)) * 2;

    if (phase_percent == 0) {
        moment->priv->moon_phase.phase = GSWE_MOON_PHASE_NEW;
    } else if (phase_percent < 25) {
        moment->priv->moon_phase.phase = GSWE_MOON_PHASE_WAXING_CRESCENT;
    } else if (phase_percent == 25) {
        moment->priv->moon_phase.phase = GSWE_MOON_PHASE_WAXING_HALF;
    } else if (phase_percent < 50) {
        moment->priv->moon_phase.phase = GSWE_MOON_PHASE_WAXING_GIBBOUS;
    } else if (phase_percent == 50) {
        moment->priv->moon_phase.phase = GSWE_MOON_PHASE_FULL;
    } else if (phase_percent < 75) {
        moment->priv->moon_phase.phase = GSWE_MOON_PHASE_WANING_GIBBOUS;
    } else if (phase_percent == 75) {
        moment->priv->moon_phase.phase = GSWE_MOON_PHASE_WANING_HALF;
    } else if (phase_percent < 100) {
        moment->priv->moon_phase.phase = GSWE_MOON_PHASE_WANING_CRESCENT;
    } else {
        moment->priv->moon_phase.phase = GSWE_MOON_PHASE_DARK;
    }

    moment->priv->moon_phase_revision = moment->priv->revision;

    return &(moment->priv->moon_phase);
}

static gint
find_aspect_by_both_planets(GsweAspectData *aspect, struct GsweAspectFinder *aspect_finder)
{
    if (((aspect->planet1->planet_id == aspect_finder->planet1) && (aspect->planet2->planet_id == aspect_finder->planet2)) || ((aspect->planet1->planet_id == aspect_finder->planet2) && (aspect->planet2->planet_id == aspect_finder->planet1))) {
        return 0;
    }

    return 1;
}

static gboolean
find_aspect(gpointer aspect_p, GsweAspectInfo *aspect_info, GsweAspectData *aspect_data)
{
    GsweAspect aspect = GPOINTER_TO_INT(aspect_p);
    gdouble diff,
            planet_orb,
            aspect_orb;

    aspect_data->distance = fabs(aspect_data->planet1->position - aspect_data->planet2->position);

    if (aspect_data->distance > 180.0) {
        aspect_data->distance = 360.0 - aspect_data->distance;
    }

    diff = fabs(aspect_info->size - aspect_data->distance);
    planet_orb = fmin(aspect_data->planet1->planet_info->orb, aspect_data->planet2->planet_info->orb);
    aspect_orb = fmax(1.0, planet_orb - aspect_info->orb_modifier);

    if (diff < aspect_orb) {
        aspect_data->aspect = aspect;
        aspect_data->aspect_info = aspect_info;

        if (aspect_info->size == 0) {
            aspect_data->difference = (1 - ((360.0 - diff) / 360.0)) * 100.0;
        } else {
            aspect_data->difference = (1 - ((aspect_info->size - diff) / aspect_info->size)) * 100.0;
        }

        return TRUE;
    }

    return FALSE;
}

static void
gswe_moment_calculate_aspects(GsweMoment *moment)
{
    GList *oplanet,
          *iplanet;

    if (moment->priv->aspect_revision == moment->priv->revision) {
        return;
    }

    gswe_moment_calculate_all_planets(moment);
    g_list_free_full(moment->priv->aspect_list, g_free);

    for (oplanet = moment->priv->planet_list; oplanet; oplanet = oplanet->next) {
        for (iplanet = moment->priv->planet_list; iplanet; iplanet = iplanet->next) {
            GswePlanetData *outer_planet = oplanet->data,
                           *inner_planet = iplanet->data;
            struct GsweAspectFinder aspect_finder;
            GsweAspectData *aspect_data;

            if (outer_planet->planet_id == inner_planet->planet_id) {
                continue;
            }

            aspect_finder.planet1 = outer_planet->planet_id;
            aspect_finder.planet2 = inner_planet->planet_id;

            if (g_list_find_custom(moment->priv->aspect_list, &aspect_finder, (GCompareFunc)find_aspect_by_both_planets) != NULL) {
                continue;
            }

            aspect_data = g_new0(GsweAspectData, 1);
            aspect_data->planet1 = outer_planet;
            aspect_data->planet2 = inner_planet;
            aspect_data->aspect = GSWE_ASPECT_NONE;

            (void)g_hash_table_find(gswe_aspect_info_table, (GHRFunc)find_aspect, aspect_data);

            if (aspect_data->aspect == GSWE_ASPECT_NONE) {
                aspect_data->aspect_info = g_hash_table_lookup(gswe_aspect_info_table, GINT_TO_POINTER(GSWE_ASPECT_NONE));
            }

            moment->priv->aspect_list = g_list_prepend(moment->priv->aspect_list, aspect_data);
        }
    }

    moment->priv->aspect_revision = moment->priv->revision;
}

/**
 * gswe_moment_get_all_aspects:
 * @moment: the GsweMoment to operate on
 *
 * Gets all planetary aspects between the planets added by
 * gswe_moment_add_planet() or gswe_moment_add_all_planets().
 *
 * Returns: (element-type GsweAspectData) (transfer none): a GList of
 *          #GsweAspectData. Both the GList and GsweAspectData objects belong
 *          to @moment, and should not be freed or modified.
 */
GList *
gswe_moment_get_all_aspects(GsweMoment *moment)
{
    gswe_moment_calculate_aspects(moment);

    return moment->priv->aspect_list;
}

/**
 * gswe_moment_get_planet_aspects:
 * @moment: the GsweMoment to operate on
 * @planet: the planet whose aspects you want to get
 * @err: a #GError
 *
 * Get all the aspects between @planet and all the other planets added with
 * gswe_moment_add_planet() or gswe_moment_add_all_planets().
 *
 * Returns: (element-type GsweAspectData) (transfer container): a #GList of
 *          #GsweAspectData. The GsweAspectData structures belong to @moment,
 *          but the GList should be freed using g_list_free(). If the planet
 *          has no aspects, or the planet has not been added to @moment,
 *          returns NULL.
 */
GList *
gswe_moment_get_planet_aspects(GsweMoment *moment, GswePlanet planet, GError **err)
{
    GList *ret = NULL,
          *aspect;

    if (!gswe_moment_has_planet(moment, planet)) {
        g_set_error(err, GSWE_MOMENT_ERROR, GSWE_MOMENT_ERROR_NONADDED_PLANET, "Specified planet is not added to the moment object");

        return NULL;
    }

    gswe_moment_calculate_aspects(moment);

    for (aspect = moment->priv->aspect_list; aspect; aspect = aspect->next) {
        GsweAspectData *aspect_data = aspect->data;

        if ((aspect_data->planet1->planet_id == planet) || (aspect_data->planet2->planet_id == planet)) {
            ret = g_list_prepend(ret, aspect_data);
        }
    }

    return ret;
}

static gboolean
find_antiscion(GsweAntiscionAxis *axis, GsweAntiscionInfo *antiscion_info, GsweAntiscionData *antiscion_data)
{
    gdouble start_point,
            axis_position,
            planet_orb;

    if (*axis == GSWE_ANTISCION_AXIS_NONE) {
        return FALSE;
    }

    planet_orb = fmin(antiscion_data->planet1->planet_info->orb, antiscion_data->planet2->planet_info->orb);
    start_point = (antiscion_info->start_sign->sign_id - 1) * 30.0;

    if (antiscion_info->middle_axis == TRUE) {
        start_point += 15.0;
    }

    axis_position = 2 * start_point - antiscion_data->planet1->position;

    if (axis_position < 0) {
        axis_position += 360.0;
    }

    if ((antiscion_data->difference = fabs(antiscion_data->planet2->position - axis_position)) <= planet_orb) {
        antiscion_data->antiscion_info = antiscion_info;
        antiscion_data->axis = *axis;

        return TRUE;
    } else {
        antiscion_data->difference = 0.0;
    }

    return FALSE;
}

static gint
find_antiscion_by_both_planets(GsweAntiscionData *antiscion, struct GsweAspectFinder *antiscion_finder)
{
    if (((antiscion->planet1->planet_id == antiscion_finder->planet1) && (antiscion->planet2->planet_id == antiscion_finder->planet2)) || ((antiscion->planet1->planet_id == antiscion_finder->planet2) && (antiscion->planet2->planet_id == antiscion_finder->planet1))) {
        return 0;
    }

    return 1;
}

static void
gswe_moment_calculate_antiscia(GsweMoment *moment)
{
    GList *oplanet,
          *iplanet;

    if (moment->priv->antiscia_revision == moment->priv->revision) {
        return;
    }

    gswe_moment_calculate_all_planets(moment);
    g_list_free_full(moment->priv->antiscia_list, g_free);

    for (oplanet = moment->priv->planet_list; oplanet; oplanet = oplanet->next) {
        for (iplanet = moment->priv->planet_list; iplanet; iplanet = iplanet->next) {
            GswePlanetData *outer_planet = oplanet->data,
                           *inner_planet = iplanet->data;
            GsweAntiscionData *antiscion_data;
            struct GsweAspectFinder antiscion_finder;

            if (outer_planet->planet_id == inner_planet->planet_id) {
                continue;
            }

            antiscion_finder.planet1 = outer_planet->planet_id;
            antiscion_finder.planet2 = inner_planet->planet_id;

            if (g_list_find_custom(moment->priv->antiscia_list, &antiscion_finder, (GCompareFunc)find_antiscion_by_both_planets) != NULL) {
                continue;
            }

            antiscion_data = g_new0(GsweAntiscionData, 1);
            antiscion_data->planet1 = outer_planet;
            antiscion_data->planet2 = inner_planet;
            antiscion_data->axis = GSWE_ANTISCION_AXIS_NONE;

            (void)g_hash_table_find(gswe_antiscion_info_table, (GHRFunc)find_antiscion, antiscion_data);

            if (antiscion_data->axis == GSWE_ANTISCION_AXIS_NONE) {
                antiscion_data->antiscion_info = g_hash_table_lookup(gswe_antiscion_info_table, GINT_TO_POINTER(GSWE_ANTISCION_AXIS_NONE));
            }

            moment->priv->antiscia_list = g_list_prepend(moment->priv->antiscia_list, antiscion_data);
        }
    }

    moment->priv->antiscia_revision = moment->priv->revision;
}

/**
 * gswe_moment_get_all_antiscia:
 * @moment: The GsweMoment object to operate on.
 *
 * Get all found antiscia between planets in @moment.
 *
 * Returns: (element-type GsweAntiscionData) (transfer none): A #GList of
 *          #GsweAntiscionData.
 */
GList *
gswe_moment_get_all_antiscia(GsweMoment *moment)
{
    gswe_moment_calculate_antiscia(moment);

    return moment->priv->antiscia_list;
}

/**
 * gswe_moment_get_all_planet_antiscia:
 * @moment: The GsweMoment object to operate on.
 * @planet: The planet whose antiscion planets are requested.
 * @err: a #GError
 *
 * Get all the antiscion planets on all registered axes for @planet.
 *
 * Returns: (element-type GsweAntiscionData) (transfer container): a #GList of
 *          #GsweAntiscionData. The GsweAntiscionData structures belong to
 *          @moment, but the GList should be freed using g_list_free(). If no
 *          planet has any antiscia, or the planet has not been added to
 *          @moment, returns NULL.
 */
GList *
gswe_moment_get_all_planet_antiscia(GsweMoment *moment, GswePlanet planet, GError **err)
{
    GList *ret = NULL,
          *antiscion;

    if (!gswe_moment_has_planet(moment, planet)) {
        g_set_error(err, GSWE_MOMENT_ERROR, GSWE_MOMENT_ERROR_NONADDED_PLANET, "Specified planet is not added to the moment object");

        return NULL;
    }

    gswe_moment_calculate_antiscia(moment);

    for (antiscion = moment->priv->antiscia_list; antiscion; antiscion = g_list_next(antiscion)) {
        GsweAntiscionData *antiscion_data = antiscion->data;

        if ((antiscion_data->planet1->planet_id == planet) || (antiscion_data->planet2->planet_id == planet)) {
            ret = g_list_prepend(ret, antiscion_data);
        }
    }

    return ret;
}

/**
 * gswe_moment_get_axis_all_antiscia:
 * @moment: The GsweMoment object to operate on.
 * @axis: The axis on which you want to search for antiscion planets.
 *
 * Get all the antiscion planets on the specified axis @axis.
 *
 * Returns: (element-type GsweAntiscionData) (transfer container): a #GList of
 *          #GsweAntiscionData. The GsweAntiscionData structures belong to @moment,
 *          but the GList should be freed using g_list_free(). If there are
 *          no antiscion planets on the given axis, returns NULL.
 */
GList *
gswe_moment_get_axis_all_antiscia(GsweMoment *moment, GsweAntiscionAxis axis)
{
    GList *ret = NULL,
          *antiscion_l;

    gswe_moment_calculate_antiscia(moment);

    for (antiscion_l = moment->priv->antiscia_list; antiscion_l; antiscion_l = g_list_next(antiscion_l)) {
        GsweAntiscionData *antiscion_data = antiscion_l->data;

        if (antiscion_data->axis == axis) {
            ret = g_list_prepend(ret, antiscion_data);
        }
    }

    return ret;
}

/**
 * gswe_moment_get_axis_planet_antiscia:
 * @moment: the GsweMoment object to operate on
 * @axis: the axis on which you want to search for antiscion planets
 * @planet: the planet whose antiscion planets are requested
 * @err: a #GError
 *
 * Get the antiscion planets of @planet as seen in @axis.
 *
 * Returns: (element-type GsweAntiscionData) (transfer container): a #GList of
 *          #GsweAntiscionData. The GsweAntiscionData structires belong to @moment,
 *          but the GList should be freed using g_list_free(). If the planet
 *          has no antiscia, or the planet has not been added to @moment,
 *          returns NULL.
 */
GList *
gswe_moment_get_axis_planet_antiscia(GsweMoment *moment, GsweAntiscionAxis axis, GswePlanet planet, GError **err)
{
    GList *ret = NULL,
          *antiscion_l;

    if (!gswe_moment_has_planet(moment, planet)) {
        g_set_error(err, GSWE_MOMENT_ERROR, GSWE_MOMENT_ERROR_NONADDED_PLANET, "Specified planet is not added to the moment object");

        return NULL;
    }

    gswe_moment_calculate_antiscia(moment);

    for (antiscion_l = moment->priv->antiscia_list; antiscion_l; antiscion_l = g_list_next(antiscion_l)) {
        GsweAntiscionData *antiscion_data = antiscion_l->data;

        if (((antiscion_data->planet1->planet_id == planet) || (antiscion_data->planet2->planet_id == planet))  && (antiscion_data->axis == axis)) {
            ret = g_list_prepend(ret, antiscion_data);
        }
    }

    return ret;
}

