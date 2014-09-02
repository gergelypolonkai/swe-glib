/* gswe-moment.c - Planetary moment object for SWE-GLib
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
#include "swe-glib.h"
#include "swe-glib-private.h"

#include "../swe/src/swephexp.h"

#define glforeach(a, b) for ((a) = (b); (a); (a) = g_list_next((a)))

/**
 * SECTION:gswe-moment
 * @short_description: an exact moment of the sky, as seen from a given point
 *                     of Earth at a given time
 * @title: GsweMoment
 * @stability: Stable
 * @include: swe-glib/swe-glib.h
 *
 * This class represents an exact moment of the sky, as it can be seen from
 * one given point on Earth at a given time.
 */

#define GSWE_MOMENT_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE( \
            (obj), \
            GSWE_TYPE_MOMENT, \
            GsweMomentPrivate))

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
 *
 * The private parts of #GsweMoment
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
    GsweMoonPhaseData *moon_phase;
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

static void gswe_moment_set_property(
        GObject *object,
        guint prop_id,
        const GValue *value,
        GParamSpec *pspec);

static void gswe_moment_get_property(
        GObject *object,
        guint prop_id,
        GValue *value,
        GParamSpec *pspec);

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
     * The ::changed signal is emitted each time the time or coordinates are
     * changed
     */
    gswe_moment_signals[SIGNAL_CHANGED] = g_signal_new(
            "changed",
            G_OBJECT_CLASS_TYPE(gobject_class),
            G_SIGNAL_RUN_FIRST,
            0,
            NULL,
            NULL,
            g_cclosure_marshal_generic,
            G_TYPE_NONE,
            0
        );

    /**
     * GsweMoment:timestamp:
     *
     * The timestamp associated with this moment
     */
    g_object_class_install_property(
            gobject_class,
            PROP_TIMESTAMP,
            g_param_spec_object(
                    "timestamp",
                    "Timestamp",
                    "Timestamp of this moment",
                    GSWE_TYPE_TIMESTAMP,
                    G_PARAM_READWRITE
                )
        );

    /**
     * GsweMoment:coordinates:
     *
     * The geographical coordinates associated with this moment
     */
    g_object_class_install_property(
            gobject_class,
            PROP_COORDINATES,
            g_param_spec_boxed(
                    "coordinates",
                    "Coordinates",
                    "Geographical coordinates",
                    GSWE_TYPE_COORDINATES,
                    G_PARAM_READWRITE
                )
        );

    /**
     * GsweMoment:house-system:
     *
     * The house system associated with this moment
     */
    g_object_class_install_property(
            gobject_class,
            PROP_HOUSE_SYSTEM,
            g_param_spec_enum(
                    "house-system",
                    "House System",
                    "Astrological house system",
                    GSWE_TYPE_HOUSE_SYSTEM,
                    GSWE_HOUSE_SYSTEM_PLACIDUS,
                    G_PARAM_READWRITE
                )
        );
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
    moment->priv->moon_phase = gswe_moon_phase_data_new();
    moment->priv->element_points = g_hash_table_new_full(
            g_direct_hash, g_direct_equal,
            NULL, NULL
        );
    moment->priv->quality_points = g_hash_table_new_full(
            g_direct_hash, g_direct_equal,
            NULL, NULL
        );
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

    g_signal_handlers_disconnect_by_func(
            moment->priv->timestamp,
            gswe_moment_timestamp_changed,
            NULL
        );

    g_clear_object(&moment->priv->timestamp);

    G_OBJECT_CLASS(gswe_moment_parent_class)->dispose(gobject);
}

static void
gswe_moment_finalize(GObject *gobject)
{
    GsweMoment *moment = GSWE_MOMENT(gobject);

    g_list_free_full(
            moment->priv->house_list,
            (GDestroyNotify)gswe_house_data_unref
        );
    g_list_free_full(
            moment->priv->planet_list,
            (GDestroyNotify)gswe_planet_data_unref
        );
    g_list_free_full(
            moment->priv->aspect_list,
            (GDestroyNotify)gswe_aspect_data_unref
        );
    g_list_free_full(
            moment->priv->antiscia_list,
            (GDestroyNotify)gswe_antiscion_data_unref
        );
    g_object_unref(moment->priv->timestamp);
    gswe_moon_phase_data_unref(moment->priv->moon_phase);
    g_hash_table_unref(moment->priv->element_points);
    g_hash_table_unref(moment->priv->quality_points);

    G_OBJECT_CLASS(gswe_moment_parent_class)->finalize(gobject);
}

static void
gswe_moment_set_property(
        GObject *object,
        guint prop_id,
        const GValue *value,
        GParamSpec *pspec)
{
    GsweMoment *moment = GSWE_MOMENT(object);

    switch (prop_id) {
        case PROP_TIMESTAMP:
            gswe_moment_set_timestamp(moment, (g_value_get_object(value)));

            break;

        case PROP_COORDINATES:
            {
                GsweCoordinates *coords = g_value_get_boxed(value);

                gswe_moment_set_coordinates(
                        moment,
                        coords->longitude,
                        coords->latitude,
                        coords->altitude
                    );
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
gswe_moment_get_property(
        GObject *object,
        guint prop_id,
        GValue *value,
        GParamSpec *pspec
    )
{
    GsweMoment *moment = GSWE_MOMENT(object);
    GsweMomentPrivate *priv = moment->priv;

    switch (prop_id) {
        case PROP_TIMESTAMP:
            g_value_set_object(value, priv->timestamp);

            break;

        case PROP_COORDINATES:
            {
                GsweCoordinates *coords = gswe_coordinates_copy(
                        &(priv->coordinates)
                    );

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
        g_signal_handlers_disconnect_by_func(
                moment->priv->timestamp,
                gswe_moment_timestamp_changed,
                NULL
            );
        g_clear_object(&moment->priv->timestamp);
    }

    moment->priv->revision++;
    moment->priv->timestamp = timestamp;
    g_object_ref(timestamp);
    g_signal_connect(
            G_OBJECT(timestamp),
            "changed",
            G_CALLBACK(gswe_moment_timestamp_changed),
            moment
        );

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
gswe_moment_set_coordinates(
        GsweMoment *moment,
        gdouble longitude,
        gdouble latitude,
        gdouble altitude)
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
 * Gets the house system associated with @moment.
 *
 * Returns: The house system currently associated with @moment
 */
GsweHouseSystem
gswe_moment_get_house_system(GsweMoment *moment)
{
    return moment->priv->house_system;
}

/**
 * gswe_moment_new:
 *
 * Creates a new, empty GsweMoment object. The object created this way can not
 * be used for any calculations yet, you need to call various gswe_moment_set_*
 * functions first. It is preferred to call gswe_moment_new_full() instead.
 *
 * Returns: (transfer full): a new GsweMoment object
 */
GsweMoment *
gswe_moment_new(void)
{
    gswe_init();

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
 * @house_system: the house system you want to use
 *
 * Creates a new GsweMoment object with the timestamp, coordinates and house
 * system set. This is the preferred way to create a GsweMoment object.
 *
 * Returns: (transfer full): a new GsweMoment object, which is usable out of
 *          the box
 */
GsweMoment *
gswe_moment_new_full(
        GsweTimestamp *timestamp,
        gdouble longitude,
        gdouble latitude,
        gdouble altitude,
        GsweHouseSystem house_system)
{
    GsweMoment *moment = gswe_moment_new();

    moment->priv->timestamp = timestamp;
    g_object_ref(timestamp);
    g_signal_connect(
            G_OBJECT(timestamp),
            "changed",
            G_CALLBACK(gswe_moment_timestamp_changed),
            moment
        );
    moment->priv->coordinates.longitude = longitude;
    moment->priv->coordinates.latitude = latitude;
    moment->priv->coordinates.altitude = altitude;
    moment->priv->house_system = house_system;

    return moment;
}

static gint
find_planet_by_id(GswePlanetData *planet_data, GswePlanet *planet)
{
    if (planet_data->planet_info == NULL) {
        return -1;
    }

    if (planet_data->planet_info->planet == *planet) {
        return 0;
    }

    return 1;
}

static void
calculate_data_by_position(
        GsweMoment *moment,
        GswePlanet planet,
        gdouble position,
        GError **err)
{
    GswePlanetData *planet_data;
    GsweZodiac sign;
    GsweSignInfo *sign_info;
    GList *result;

    if ((result = g_list_find_custom(
                    moment->priv->planet_list,
                    &planet,
                    (GCompareFunc)find_planet_by_id
                )) == NULL) {
        return;
    }

    if ((planet_data = (GswePlanetData *)(result->data)) == NULL) {
        return;
    }

    if (planet_data->revision == moment->priv->revision) {
        return;
    }

    sign = (GsweZodiac)ceil(position / 30.0);

    // If position happens to be exactly 0, this calculation yields
    // GSWE_SIGN_NONE, but should be GSWE_SIGN_ARIES
    if (sign == GSWE_SIGN_NONE) {
        sign = GSWE_SIGN_ARIES;
    }

    if ((sign_info = g_hash_table_lookup(
                    gswe_sign_info_table,
                    GINT_TO_POINTER(sign)
                )) == NULL) {
        g_error("Calculations brought an unknown sign!");
    }

    planet_data->position = position;
    planet_data->retrograde = FALSE;
    planet_data->house = gswe_moment_get_house(moment, position, err);
    planet_data->sign_info = gswe_sign_info_ref(sign_info);
    planet_data->revision = moment->priv->revision;
}

static void
gswe_moment_calculate_house_positions(GsweMoment *moment, GError **err)
{
    gdouble cusps[13],
            ascmc[10],
            jd;
    gint i;
    GsweHouseSystemInfo *house_system_info;

    if (moment->priv->house_revision == moment->priv->revision) {
        return;
    }

    g_list_free_full(
            moment->priv->house_list,
            (GDestroyNotify)gswe_house_data_unref
        );
    moment->priv->house_list = NULL;

    // If no house system is set, we need no calculations at all. Just leave
    // the list empty and return
    if (moment->priv->house_system == GSWE_HOUSE_SYSTEM_NONE) {
        moment->priv->house_revision = moment->priv->revision;

        return;
    }

    if ((house_system_info = g_hash_table_lookup(
                    gswe_house_system_info_table,
                    GINT_TO_POINTER(moment->priv->house_system)
                )) == NULL) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_HSYS,
                "Unknown house system"
            );

        return;
    }

    jd = gswe_timestamp_get_julian_day_et(moment->priv->timestamp, err);

    // If Julian Day calculation yields error, we don't do anything. err is
    // already filled with the error message, so let's just return
    if ((err) && (*err)) {
        return;
    }

    swe_houses(
            jd,
            moment->priv->coordinates.latitude,
            moment->priv->coordinates.longitude,
            house_system_info->sweph_id,
            cusps,
            ascmc
        );

    /* TODO: SWE house system 'G' (Gauquelin sector cusps) have 36 houses; we
     * should detect that somehow (house system 'G' is not implemented yet in
     * GsweHouseSystem, and all other house systems have exactly 12 houses, so
     * this should not cause trouble yet, though) */
    for (i = 12; i >= 1; i--) {
        GsweSignInfo *sign_info;
        GsweHouseData *house_data = gswe_house_data_new();

        house_data->house = i;
        house_data->cusp_position = cusps[i];

        if ((sign_info = g_hash_table_lookup(
                        gswe_sign_info_table,
                        GINT_TO_POINTER((gint)ceilf(cusps[i] / 30.0))
                    )) == NULL) {
            g_list_free_full(
                    moment->priv->house_list,
                    (GDestroyNotify)gswe_house_data_unref
                );
            moment->priv->house_list = NULL;
            moment->priv->house_revision = 0;
            g_set_error(
                    err,
                    GSWE_ERROR, GSWE_ERROR_UNKNOWN_SIGN,
                    "Calculation brought an unknown sign"
                );

            return;
        }

        house_data->sign_info = gswe_sign_info_ref(sign_info);
        moment->priv->house_list = g_list_prepend(
                moment->priv->house_list,
                house_data
            );
    }

    moment->priv->house_revision = moment->priv->revision;

    // The Ascendant, MC and Vertex points are also calculated by swe_houses(),
    // so let's update them.
    if (gswe_moment_has_planet(moment, GSWE_PLANET_ASCENDANT)) {
        calculate_data_by_position(
                moment,
                GSWE_PLANET_ASCENDANT,
                ascmc[0],
                err
            );
    }

    if (gswe_moment_has_planet(moment, GSWE_PLANET_MC)) {
        calculate_data_by_position(moment, GSWE_PLANET_MC, ascmc[1], err);
    }

    if (gswe_moment_has_planet(moment, GSWE_PLANET_VERTEX)) {
        calculate_data_by_position(moment, GSWE_PLANET_VERTEX, ascmc[3], err);
    }
}

/**
 * gswe_moment_get_house_cusps:
 * @moment: The GsweMoment object to operate on
 * @err: a #GError
 *
 * Calculate house cusp positions based on the house system, location and time
 * set in @moment.
 *
 * Returns: (element-type GsweHouseData) (transfer none): a GList of
 * #GsweHouseData
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
 * Checks if @planet is added to @moment, e.g. its position and related data is
 * calculated.
 *
 * Returns: #TRUE if @planet is already added to @moment, #FALSE otherwise
 */
gboolean
gswe_moment_has_planet(GsweMoment *moment, GswePlanet planet)
{
    return (g_list_find_custom(
                moment->priv->planet_list,
                &planet,
                (GCompareFunc)find_planet_by_id
            ) != NULL);
}

/**
 * gswe_moment_add_planet:
 * @moment: a GsweMoment object
 * @planet: the planet to add
 * @err: a #GError
 *
 * Adds @planet to the calculated planets of @moment. @err is populated with
 * GSWE_ERROR_UNKNOWN_PLANET if the given planet is not known to SWE-GLib.
 */
void
gswe_moment_add_planet(GsweMoment *moment, GswePlanet planet, GError **err)
{
    GswePlanetData *planet_data;
    GswePlanetInfo *planet_info;

    if (gswe_moment_has_planet(moment, planet)) {
        return;
    }

    if ((planet_info = g_hash_table_lookup(
                    gswe_planet_info_table,
                    GINT_TO_POINTER(planet)
                )) == NULL) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_PLANET,
                "Unknown planet"
            );

        return;
    }

    planet_data = gswe_planet_data_new();
    planet_data->planet_info = gswe_planet_info_ref(planet_info);
    planet_data->revision = 0;

    moment->priv->planet_list = g_list_append(
            moment->priv->planet_list,
            planet_data
        );
}

static void
planet_add(gpointer key, gpointer value, GsweMoment *moment)
{
    GswePlanet planet = (GswePlanet)GPOINTER_TO_INT(key);

    gswe_moment_add_planet(moment, planet, NULL);
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
    g_hash_table_foreach(gswe_planet_info_table, (GHFunc)planet_add, moment);
}

static void
gswe_moment_calculate_planet(GsweMoment *moment,
                             GswePlanet planet,
                             GError     **err)
{
    GswePlanetData *planet_data;
    gpointer       data         = g_list_find_custom(
            moment->priv->planet_list,
            &planet,
            (GCompareFunc)find_planet_by_id
        );

    g_return_if_fail(data != NULL);

    planet_data = (GswePlanetData *)(g_list_find_custom(
                moment->priv->planet_list,
                &planet,
                (GCompareFunc)find_planet_by_id
            )->data);
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

    swe_set_topo(
            moment->priv->coordinates.longitude,
            moment->priv->coordinates.latitude,
            moment->priv->coordinates.altitude
        );
    jd = gswe_timestamp_get_julian_day_et(moment->priv->timestamp, err);

    if (planet_data->planet_info->real_body == FALSE) {
        if (
            (planet_data->planet_info->planet != GSWE_PLANET_ASCENDANT)
            && (planet_data->planet_info->planet != GSWE_PLANET_MC)
            && (planet_data->planet_info->planet != GSWE_PLANET_VERTEX)
        ) {
            g_warning(
                    "The position data of planet %d can not be "
                    "calculated by this function",
                    planet
                );

            return;
        } else {
            // gswe_moment_calculate_house_positions() calculates house cusp
            // positions, together with Ascendant, MC and Vertex points
            gswe_moment_calculate_house_positions(moment, err);

            return;
        }
    }

    if ((err) && (*err)) {
        return;
    }

    if ((ret = swe_calc(
                    jd,
                    planet_data->planet_info->sweph_id,
                    SEFLG_SPEED | SEFLG_TOPOCTR,
                    x2,
                    serr
                )) < 0) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_SWE_FATAL,
                "Swiss Ephemeris error: %s",
                serr
            );

        return;
    } else if (ret != (SEFLG_SPEED | SEFLG_TOPOCTR)) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_SWE_NONFATAL,
                "Swiss Ephemeris error: %s",
                serr
            );
    }

    calculate_data_by_position(moment, planet, x2[0], &calc_err);

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
    if (planet_data->planet_info) {
        gswe_moment_calculate_planet(
                moment,
                planet_data->planet_info->planet,
                NULL
            );
    } else {
        g_warning(
                "planet_data holds no planet. This is a possible "
                    "bug in SWE-GLib, or in your application."
            );
    }
}

static void
gswe_moment_calculate_all_planets(GsweMoment *moment)
{
    g_list_foreach(moment->priv->planet_list, (GFunc)calculate_planet, moment);
}

/**
 * gswe_moment_get_all_planets:
 * @moment: The GsweMoment to operate on
 *
 * Get all the planets added to @moment.
 *
 * Returns: (element-type GswePlanetData) (transfer none): A #GList of
 *          #GswePlanetData.
 */
GList *
gswe_moment_get_all_planets(GsweMoment *moment)
{
    gswe_moment_calculate_all_planets(moment);

    return moment->priv->planet_list;
}

/**
 * gswe_moment_get_sign_planets:
 * @moment: a GsweMoment
 * @sign: the sign of whose planets are requested
 *
 * Gets the list of planets in @sign.
 *
 * Returns: (transfer container) (element-type GswePlanetData): a #GList of
 * #GswePlanetData.
 */
GList *
gswe_moment_get_sign_planets(GsweMoment *moment, GsweZodiac sign)
{
    GList *ret = NULL,
          *planet;

    gswe_moment_calculate_all_planets(moment);

    glforeach (planet, moment->priv->planet_list) {
        GswePlanetData *pd = planet->data;

        if (pd->sign_info->sign == sign) {
            ret = g_list_prepend(ret, pd);
        }
    }

    return ret;
}

/**
 * gswe_moment_get_house_planets:
 * @moment: a GsweMoment
 * @house: a house number
 *
 * Gets the list of planets in house @house.
 *
 * Returns: (transfer container) (element-type GswePlanetData): a #GList of
 * #GswePlanetData
 */
GList *
gswe_moment_get_house_planets(GsweMoment *moment, guint house)
{
    GList *ret = NULL,
          *planet;

    // If the house system is none, we always return NULL
    if (moment->priv->house_system == GSWE_HOUSE_SYSTEM_NONE) {
        return NULL;
    }

    gswe_moment_calculate_all_planets(moment);

    glforeach (planet, moment->priv->planet_list) {
        GswePlanetData *pd = planet->data;

        if (pd->house == house) {
            ret = g_list_prepend(ret, pd);
        }
    }

    return ret;
}

/**
 * gswe_moment_get_house:
 * @moment: a GsweMoment object
 * @position: an ecliptic position
 * @err: a #GError
 *
 * Returns the number of the house in which @position is.
 *
 * Returns: the number of the house in which @position is. This function always
 *          yields 0 if the associated house system is #GSWE_HOUSE_SYSTEM_NONE.
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
        gdouble cusp_i = *(gdouble *)g_list_nth_data(
                moment->priv->house_list,
                i - 1
            ),
                cusp_j = *(gdouble *)g_list_nth_data(
                        moment->priv->house_list,
                        j - 1
                    );

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

/**
 * gswe_moment_get_planet:
 * @moment: a GsweMoment
 * @planet: the planet whose data is requested
 * @err: a #GError
 *
 * Gets @planet's data, like its position, house number, sign, etc. @err is
 * populated if the planetary information can not be calculated.
 *
 * WARNING! @err may be populated if the Swiss Ephemeris data files are not
 * found. For some planets, position data still can be calculated (the results
 * will not be that exact, though). @err is populatet only to carry this
 * warning. Thus, you should always provide a non-NULL value for @err, and
 * always check it after calling this function.
 *
 * Returns: (transfer full): @planet's data
 */
GswePlanetData *
gswe_moment_get_planet(GsweMoment *moment, GswePlanet planet, GError **err)
{
    GList *planet_element;
    GswePlanetData *planet_data;

    if ((planet_element = g_list_find_custom(
                    moment->priv->planet_list,
                    &planet,
                    (GCompareFunc)find_planet_by_id
                )) == NULL) {
        return NULL;
    }

    planet_data = (GswePlanetData *)(planet_element->data);

    if (planet_data == NULL) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_PLANET,
                "Specified planet is not added to the moment object"
            );

        return NULL;
    }

    gswe_moment_calculate_planet(moment, planet, err);

    return gswe_planet_data_ref(planet_data);
}

static void
add_points(GswePlanetData *planet_data, GsweMoment *moment)
{
    guint          point;
    GsweSignInfo   *sign_info;
    GswePlanetInfo *planet_info;
    GsweElement    element;
    GsweQuality    quality;

    gswe_moment_calculate_planet(
            moment,
            planet_data->planet_info->planet,
            NULL
        );

    sign_info = gswe_planet_data_get_sign_info(planet_data);

    if (G_UNLIKELY(sign_info == NULL)) {
        g_error("Planet data calculation failed");
    }

    planet_info = gswe_planet_data_get_planet_info(planet_data);

    if (G_UNLIKELY(planet_info == NULL)) {
        g_error("Planet data calculation failed. No planet info.");
    }

    element = gswe_sign_info_get_element(sign_info);
    point   = GPOINTER_TO_INT(g_hash_table_lookup(
                moment->priv->element_points,
                GINT_TO_POINTER(element)
        )) + gswe_planet_info_get_points(planet_info);
    g_hash_table_replace(
            moment->priv->element_points,
            GINT_TO_POINTER(element),
            GINT_TO_POINTER(point)
        );

    quality = gswe_sign_info_get_quality(sign_info);
    point   = GPOINTER_TO_INT(g_hash_table_lookup(
                moment->priv->quality_points,
                GINT_TO_POINTER(quality)
        )) + gswe_planet_info_get_points(planet_info);
    g_hash_table_replace(
            moment->priv->quality_points,
            GINT_TO_POINTER(quality),
            GINT_TO_POINTER(point)
        );
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

/**
 * gswe_moment_get_element_points:
 * @moment: a GsweMoment
 * @element: the element whose point value is requested
 *
 * Gets the point value of the @element element.
 *
 * Returns: the point value
 */
guint
gswe_moment_get_element_points(GsweMoment *moment, GsweElement element)
{
    guint point;

    gswe_moment_calculate_points(moment);

    point = GPOINTER_TO_INT(g_hash_table_lookup(
                moment->priv->element_points,
                GINT_TO_POINTER(element)
            ));

    return point;
}

/**
 * gswe_moment_get_quality_points:
 * @moment: a GsweMoment
 * @quality: the quality whose point value is requested
 *
 * Gets the point value of the @quality quality.
 *
 * Returns: the point value
 */
guint
gswe_moment_get_quality_points(GsweMoment *moment, GsweQuality quality)
{
    guint point;

    gswe_moment_calculate_points(moment);

    point = GPOINTER_TO_INT(g_hash_table_lookup(
                moment->priv->quality_points,
                GINT_TO_POINTER(quality)
            ));

    return point;
}

/**
 * gswe_moment_get_moon_phase:
 * @moment: a GsweMoment
 * @err: a #GError
 *
 * Gets the phase of the Moon.
 *
 * Returns: (transfer full): a #GsweMoonPhaseData representing the phase of the
 *          Moon
 */
GsweMoonPhaseData *
gswe_moment_get_moon_phase(GsweMoment *moment, GError **err)
{
    if (moment->priv->moon_phase_revision == moment->priv->revision) {
        return moment->priv->moon_phase;
    }

    gswe_moon_phase_data_calculate_by_timestamp(
            moment->priv->moon_phase,
            moment->priv->timestamp,
            err
        );

    if (!err || !*err) {
        moment->priv->moon_phase_revision = moment->priv->revision;
    }

    return gswe_moon_phase_data_ref(moment->priv->moon_phase);
}

static gint
find_aspect_by_both_planets(
        GsweAspectData *aspect,
        struct GsweAspectFinder *aspect_finder)
{
    if (
        (
            (aspect->planet1->planet_info->planet == aspect_finder->planet1)
            && (aspect->planet2->planet_info->planet == aspect_finder->planet2)
        )
        || (
            (aspect->planet1->planet_info->planet == aspect_finder->planet2)
            && (aspect->planet2->planet_info->planet == aspect_finder->planet1)
        )
    ) {
        return 0;
    }

    return 1;
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
    g_list_free_full(
            moment->priv->aspect_list,
            (GDestroyNotify)gswe_aspect_data_unref
        );
    moment->priv->aspect_list = NULL;

    for (
            oplanet = moment->priv->planet_list;
            oplanet;
            oplanet = g_list_next(oplanet)) {
        for (
                iplanet = moment->priv->planet_list;
                iplanet;
                iplanet = g_list_next(iplanet)) {
            GswePlanetData *outer_planet = oplanet->data,
                           *inner_planet = iplanet->data;
            struct GsweAspectFinder aspect_finder;
            GsweAspectData *aspect_data;
            GList *aspect_data_element;

            if (outer_planet->planet_info->planet
                    == inner_planet->planet_info->planet
                ) {
                continue;
            }

            aspect_finder.planet1 = outer_planet->planet_info->planet;
            aspect_finder.planet2 = inner_planet->planet_info->planet;

            if ((aspect_data_element = g_list_find_custom(
                            moment->priv->aspect_list,
                            &aspect_finder,
                            (GCompareFunc)find_aspect_by_both_planets
                        )) != NULL) {
                gswe_aspect_data_calculate(aspect_data_element->data);
            } else {
                aspect_data = gswe_aspect_data_new_with_planets(
                        inner_planet,
                        outer_planet
                    );
                moment->priv->aspect_list = g_list_prepend(
                        moment->priv->aspect_list,
                        aspect_data
                    );
            }
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
gswe_moment_get_planet_aspects(
        GsweMoment *moment,
        GswePlanet planet,
        GError **err)
{
    GList *ret = NULL,
          *aspect;

    if (!gswe_moment_has_planet(moment, planet)) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_PLANET,
                "Specified planet is not added to the moment object"
            );

        return NULL;
    }

    gswe_moment_calculate_aspects(moment);

    for (
            aspect = moment->priv->aspect_list;
            aspect;
            aspect = g_list_next(aspect)
        ) {
        GsweAspectData *aspect_data = aspect->data;

        if (
            (aspect_data->planet1->planet_info->planet == planet)
            || (aspect_data->planet2->planet_info->planet == planet)
        ) {
            ret = g_list_prepend(ret, aspect_data);
        }
    }

    return ret;
}

/**
 * gswe_moment_get_aspect_by_planets:
 * @moment: the GsweMoment to operate on
 * @planet1: the first planet
 * @planet2: the second planet
 * @err: a #GError
 *
 * Get the aspect between two given planets. The order of @planet1 and @planet2
 * doesn’t matter.
 *
 * Returns: (transfer none): a #GsweAspectData containing the aspect data of the
 *          two planets. If an error occurs, like when one of the planets are
 *          not added to the planet list, returns NULL, and @err is set
 *          accordingly.
 */
GsweAspectData *
gswe_moment_get_aspect_by_planets(
        GsweMoment *moment,
        GswePlanet planet1,
        GswePlanet planet2,
        GError **err)
{
    struct GsweAspectFinder aspect_finder;
    GList *aspect_data_element;

    if (
            !gswe_moment_has_planet(moment, planet1)
            || !gswe_moment_has_planet(moment, planet2)
        ) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_PLANET,
                "One of the requested planets is not found in the planet list"
            );

        return NULL;
    }

    aspect_finder.planet1 = planet1;
    aspect_finder.planet2 = planet2;

    if ((aspect_data_element = g_list_find_custom(
                    moment->priv->aspect_list,
                    &aspect_finder,
                    (GCompareFunc)find_aspect_by_both_planets
                )) != NULL) {
        return aspect_data_element->data;
    }

    return NULL;
}

static gint
find_antiscion_by_both_planets(
        GsweAntiscionData *antiscion,
        struct GsweAspectFinder *antiscion_finder)
{
    if (
        (
            (antiscion->planet1->planet_info->planet
                == antiscion_finder->planet1)
            && (antiscion->planet2->planet_info->planet
                == antiscion_finder->planet2)
        )
        || (
            (antiscion->planet1->planet_info->planet
                == antiscion_finder->planet2)
            && (antiscion->planet2->planet_info->planet
                == antiscion_finder->planet1)
        )
    ) {
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
    g_list_free_full(
            moment->priv->antiscia_list,
            (GDestroyNotify)gswe_antiscion_data_unref
        );
    moment->priv->antiscia_list = NULL;

    for (
            oplanet = moment->priv->planet_list;
            oplanet;
            oplanet = g_list_next(oplanet)
        ) {
        for (
                iplanet = moment->priv->planet_list;
                iplanet;
                iplanet = g_list_next(iplanet)
            ) {
            GswePlanetData *outer_planet = oplanet->data,
                           *inner_planet = iplanet->data;
            struct GsweAspectFinder antiscion_finder;
            GsweAntiscionData *antiscion_data;
            GList *antiscion_data_element;

            if (outer_planet->planet_info->planet
                    == inner_planet->planet_info->planet
                ) {
                continue;
            }

            antiscion_finder.planet1 = outer_planet->planet_info->planet;
            antiscion_finder.planet2 = inner_planet->planet_info->planet;

            if ((antiscion_data_element = g_list_find_custom(
                            moment->priv->antiscia_list,
                            &antiscion_finder,
                            (GCompareFunc)find_antiscion_by_both_planets)
                    ) != NULL) {
                gswe_antiscion_data_calculate(antiscion_data_element->data);
            } else {
                antiscion_data = gswe_antiscion_data_new_with_planets(
                        inner_planet,
                        outer_planet
                    );
                moment->priv->antiscia_list = g_list_prepend(
                        moment->priv->antiscia_list,
                        antiscion_data
                    );
            }
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
gswe_moment_get_all_planet_antiscia(
        GsweMoment *moment,
        GswePlanet planet,
        GError **err)
{
    GList *ret = NULL,
          *antiscion_l;

    if (!gswe_moment_has_planet(moment, planet)) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_PLANET,
                "Specified planet is not added to the moment object"
            );

        return NULL;
    }

    gswe_moment_calculate_antiscia(moment);

    glforeach (antiscion_l, moment->priv->antiscia_list) {
        GsweAntiscionData *antiscion_data = antiscion_l->data;

        if (
                (antiscion_data->planet1->planet_info->planet == planet)
                || (antiscion_data->planet2->planet_info->planet == planet)
            ) {
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
 *          #GsweAntiscionData. The GsweAntiscionData structures belong to
 *          @moment, but the GList should be freed using g_list_free(). If
 *          there are no antiscion planets on the given axis, returns NULL.
 */
GList *
gswe_moment_get_axis_all_antiscia(GsweMoment *moment, GsweAntiscionAxis axis)
{
    GList *ret = NULL,
          *antiscion_l;

    gswe_moment_calculate_antiscia(moment);

    glforeach (antiscion_l, moment->priv->antiscia_list) {
        GsweAntiscionData *antiscion_data = antiscion_l->data;

        if (antiscion_data->antiscion_axis_info->axis == axis) {
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
 *          #GsweAntiscionData. The GsweAntiscionData structires belong to
 *          @moment, but the GList should be freed using g_list_free(). If the
 *          planet has no antiscia, or the planet has not been added to
 *          @moment, returns NULL.
 */
GList *
gswe_moment_get_axis_planet_antiscia(
        GsweMoment *moment,
        GsweAntiscionAxis axis,
        GswePlanet planet,
        GError **err)
{
    GList *ret = NULL,
          *antiscion_l;

    if (!gswe_moment_has_planet(moment, planet)) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_PLANET,
                "Specified planet is not added to the moment object"
            );

        return NULL;
    }

    gswe_moment_calculate_antiscia(moment);

    glforeach (antiscion_l, moment->priv->antiscia_list) {
        GsweAntiscionData *antiscion_data = antiscion_l->data;

        if (
            (
                (antiscion_data->planet1->planet_info->planet == planet)
                || (antiscion_data->planet2->planet_info->planet == planet)
            )
            && (antiscion_data->antiscion_axis_info->axis == axis)
        ) {
            ret = g_list_prepend(ret, antiscion_data);
        }
    }

    return ret;
}

/**
 * gswe_moment_get_antiscion_by_planets:
 * @moment: the GsweMoment to operate on
 * @planet1: the first planet
 * @planet2: the second planet
 * @err: a #GError
 *
 * Get the aspect between two given planets. The order of @planet1 and @planet2
 * doesn’t matter.
 *
 * Returns: (transfer none): a #GsweAspectData containing the aspect data of the
 *          two planets. If an error occurs, like when one of the planets are
 *          not added to the planet list, returns NULL, and @err is set
 *          accordingly.
 */
GsweAntiscionData *
gswe_moment_get_antiscion_by_planets(
        GsweMoment *moment,
        GswePlanet planet1,
        GswePlanet planet2,
        GError **err)
{
    struct GsweAspectFinder antiscion_finder;
    GList *antiscion_data_element;

    if (
            !gswe_moment_has_planet(moment, planet1)
            || !gswe_moment_has_planet(moment, planet2)
        ) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_PLANET,
                "One of the planets is not found in the planet list"
            );

        return NULL;
    }

    antiscion_finder.planet1 = planet1;
    antiscion_finder.planet2 = planet2;

    if ((antiscion_data_element = g_list_find_custom(
                    moment->priv->antiscia_list,
                    &antiscion_finder,
                    (GCompareFunc)find_antiscion_by_both_planets
                )) != NULL) {
        return antiscion_data_element->data;
    }

    return NULL;
}

