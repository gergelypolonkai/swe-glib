/* SWE-GLib - GLib style wrapper library around Astrodienst's Swiss Ephemeris
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
#include <glib.h>
#define GETTEXT_PACKAGE "swe-glib"
#include <glib/gi18n-lib.h>

#include "../swe/src/swephexp.h"
#include "swe-glib.h"
#include "swe-glib-private.h"

/**
 * SECTION:swe-glib
 * @short_description: Utility and initialization functions
 * @title: Utility functions
 * @stability: Stable
 * @include: swe-glib/swe-glib.h
 *
 * Basic utility and initialization functions. They don't operate on SWE-GLib's
 * objects, but on the library as a whole, including global tables.
 */

/**
 * GsweError:
 * @GSWE_ERROR_SUCCESS: No error
 * @GSWE_ERROR_SWE_NONFATAL: Non-fatal Swiss Ephemeris library error
 * @GSWE_ERROR_SWE_FATAL: Fatal Swiss Ephemeris library error
 * @GSWE_ERROR_INVALID_DATE: The specified Gregorian date is invalid
 * @GSWE_ERROR_INVALID_TIME: The specified time is invalid
 * @GSWE_ERROR_NO_VALID_VALUE: the #GsweTimestamp object holds no valid values
 * @GSWE_ERROR_UNKNOWN_HSYS: the requested house system is unknown
 * @GSWE_ERROR_UNKNOWN_SIGN: an invalid zodiac sign would have been returned
 * @GSWE_ERROR_UNKNOWN_PLANET: the referenced planet was not added with
 *                             gswe_moment_add_planet()
 * @GSWE_ERROR_UNKNOWN_ANTISCION_AXIS: the given axis is unknown to SWE-GLib
 * @GSWE_ERROR_UNKNOWN_ASPECT: the given aspect is unknown to SWE-GLib
 *
 * Error codes returned by the SWE-GLib functions.
 */

/**
 * GSWE_ERROR:
 *
 * Error domain for SWE-GLib in general. Since 2.0, all errors generated by
 * SWE-GLib functions are from this domain. See #GError for more information on
 * error domains.
 */

gboolean gswe_initialized = FALSE;
gchar *gswe_ephe_path = NULL;
GHashTable *gswe_planet_info_table;
GHashTable *gswe_sign_info_table;
GHashTable *gswe_house_system_info_table;
GHashTable *gswe_aspect_info_table;
GHashTable *gswe_antiscion_axis_info_table;
GsweTimestamp *gswe_full_moon_base_date;
static gboolean gswe_initializing = FALSE;

#define ADD_PLANET(ht, v, i, s, r, n, o, h) \
    (v) = gswe_planet_info_new(); \
    (v)->planet = (i); \
    (v)->sweph_id = (s); \
    (v)->real_body = (r); \
    (v)->orb = (o); \
    (v)->name = g_strdup(n); \
    (v)->points = (h); \
    g_hash_table_replace((ht), GINT_TO_POINTER(i), (v)); \

#define ADD_SIGN(ht, v, s, n, e, q) \
    (v) = gswe_sign_info_new(); \
    (v)->sign = (s); \
    (v)->name = g_strdup(n); \
    (v)->element = (e); \
    (v)->quality = (q); \
    g_hash_table_replace((ht), GINT_TO_POINTER(s), (v)); \

#define ADD_HOUSE_SYSTEM(ht, v, i, s, n) \
    (v) = gswe_house_system_info_new(); \
    (v)->house_system = i; \
    (v)->sweph_id = s; \
    (v)->name = g_strdup(n); \
    g_hash_table_replace((ht), GINT_TO_POINTER(i), (v)); \

#define ADD_ASPECT(ht, v, i, n, s, o, h, m) \
    (v) = gswe_aspect_info_new(); \
    (v)->aspect = (i); \
    (v)->name = g_strdup(n); \
    (v)->size = (s); \
    (v)->orb_modifier = (o); \
    (v)->harmonic = (h); \
    (v)->major = (m); \
    g_hash_table_replace((ht), GINT_TO_POINTER(i), (v)); \

#define ADD_ANTISCION(ht, v, hts, vs, i, n, s, m) \
    (v) = gswe_antiscion_axis_info_new(); \
    (vs) = g_hash_table_lookup((hts), GINT_TO_POINTER(i)); \
    (v)->axis = (i); \
    (v)->start_sign = (vs); \
    (v)->name = g_strdup(n); \
    (v)->sign_offset = m; \
    g_hash_table_replace((ht), GINT_TO_POINTER(i), (v)); \

/**
 * gswe_error_quark:
 *
 * Gets the SWE-GLib Error Quark.
 *
 * Return value: a #GQuark
 */
#if GLIB_CHECK_VERSION(2, 34, 0)
G_DEFINE_QUARK(gswe-error-quark, gswe_error);
#else
GQuark
gswe_error_quark(void)
{
    return g_quark_from_static_string("gswe-error-quark");
}
#endif

/**
 * gswe_init_with_dir:
 * @directory: the path that contains the Swiss Ephemeris data files
 *
 * Initializes the SWE-GLib library with @directory as the Swiss Ephemeris
 * data files' location. This, or gswe_init() must be called before any
 * calculations are made.
 */
void gswe_init_with_dir(gchar *directory)
{
    GswePlanetInfo *planet_info;
    GsweSignInfo *sign_info;
    GsweHouseSystemInfo *house_system_info;
    GsweAspectInfo *aspect_info;
    GsweAntiscionAxisInfo *antiscion_axis_info;

    if (gswe_initialized) {
        return;
    }

    if (gswe_initializing) {
        return;
    }

    gswe_initializing = TRUE;

    /* Before 2.36, g_type_init() must have been called. Let's do it! */
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif

    bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");

    gswe_planet_info_table = g_hash_table_new_full(
            g_direct_hash, g_direct_equal,
            NULL, (GDestroyNotify)gswe_planet_info_unref
        );

    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_ASCENDANT,
            -1,
            FALSE,
            _("Ascendant"),
            9.0,
            2
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
               GSWE_PLANET_DESCENDANT,
               -1,
               FALSE,
               _("Descendant"),
               0.0,
               0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_MC,
            -1,
            FALSE,
            _("Midheaven"),
            5.0,
            1
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
               GSWE_PLANET_IC,
               -1,
               FALSE,
               _("Immum Coeli"),
               0.0,
               0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_VERTEX,
            -1,
            FALSE,
            _("Vertex"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
               GSWE_PLANET_ANTIVERTEX,
               -1,
               FALSE,
               _("Anti-vertex"),
               0.0,
               0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_MOON_NODE,
            SE_MEAN_NODE,
            TRUE,
            _("Ascending Moon Node"),
            2.0,
            1
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
               GSWE_PLANET_MOON_SOUTH_NODE,
               // As this is just the opposing point of the mean node,
               // we actually calculate that, and simply add 180
               // degrees when queried.
               SE_MEAN_NODE,
               TRUE,
               _("Descending Moon Node"),
               2.0,
               0);
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_MOON_APOGEE,
            SE_MEAN_APOG,
            TRUE,
            _("Dark Moon"),
            2.0,
            0
        );

    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_SUN,
            SE_SUN,
            TRUE,
            _("Sun"),
            13.0,
            2
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_MOON,
            SE_MOON,
            TRUE,
            _("Moon"),
            9.0,
            2
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_MERCURY,
            SE_MERCURY,
            TRUE,
            _("Mercury"),
            7.0,
            2
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_VENUS,
            SE_VENUS,
            TRUE,
            _("Venus"),
            7.0,
            1
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_MARS,
            SE_MARS,
            TRUE,
            _("Mars"),
            7.0,
            1
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_JUPITER,
            SE_JUPITER,
            TRUE,
            _("Jupiter"),
            9.0,
            1
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_SATURN,
            SE_SATURN,
            TRUE,
            _("Saturn"),
            7.0,
            1
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_URANUS,
            SE_URANUS,
            TRUE,
            _("Uranus"),
            5.0,
            1
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_NEPTUNE,
            SE_NEPTUNE,
            TRUE,
            _("Neptune"),
            5.0,
            1
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_PLUTO,
            SE_PLUTO,
            TRUE,
            _("Pluto"),
            3.0,
            1
        );

    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_CHIRON,
            SE_CHIRON,
            TRUE,
            _("Chiron"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_CERES,
            SE_CERES,
            TRUE,
            _("Ceres"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_PALLAS,
            SE_PALLAS,
            TRUE,
            _("Pallas"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_JUNO,
            SE_JUNO,
            TRUE,
            _("Juno"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_VESTA,
            SE_VESTA,
            TRUE,
            _("Vesta"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_PHOLUS,
            SE_PHOLUS,
            TRUE,
            _("Pholus"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_NESSUS,
            SE_AST_OFFSET + 7066,
            TRUE,
            _("Nessus"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_CHARIKLO,
            SE_AST_OFFSET + 10199,
            TRUE,
            _("Chariklo"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_SEDNA,
            SE_AST_OFFSET + 90377,
            TRUE,
            _("Sedna"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_ERIS,
            SE_AST_OFFSET + 136199,
            TRUE,
            _("Eris"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_DEJANIRA,
            SE_AST_OFFSET + 157,
            TRUE,
            _("Dejanira"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_CIRCE,
            SE_AST_OFFSET + 34,
            TRUE,
            _("Circe"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_ORCUS,
            SE_AST_OFFSET + 90482,
            TRUE,
            _("Orcus"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_ASBOLUS,
            SE_AST_OFFSET + 8405,
            TRUE,
            _("Asbolus"),
            2.0,
            0
        );
    ADD_PLANET(gswe_planet_info_table, planet_info,
            GSWE_PLANET_HYGIEA,
            SE_AST_OFFSET + 10,
            TRUE,
            _("Hygiea"),
            2.0,
            0
        );

    gswe_sign_info_table = g_hash_table_new_full(
            g_direct_hash, g_direct_equal,
            NULL, (GDestroyNotify)gswe_sign_info_unref
        );

    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_ARIES,
            _("Aries"),
            GSWE_ELEMENT_FIRE,
            GSWE_QUALITY_CARDINAL
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_TAURUS,
            _("Taurus"),
            GSWE_ELEMENT_EARTH,
            GSWE_QUALITY_FIX
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_GEMINI,
            _("Gemini"),
            GSWE_ELEMENT_AIR,
            GSWE_QUALITY_MUTABLE
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_CANCER,
            _("Cancer"),
            GSWE_ELEMENT_WATER,
            GSWE_QUALITY_CARDINAL
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_LEO,
            _("Leo"),
            GSWE_ELEMENT_FIRE,
            GSWE_QUALITY_FIX
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_VIRGO,
            _("Virgo"),
            GSWE_ELEMENT_EARTH,
            GSWE_QUALITY_MUTABLE
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_LIBRA,
            _("Libra"),
            GSWE_ELEMENT_AIR,
            GSWE_QUALITY_CARDINAL
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_SCORPIO,
            _("Scorpio"),
            GSWE_ELEMENT_WATER,
            GSWE_QUALITY_FIX
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_SAGITTARIUS,
            _("Sagittarius"),
            GSWE_ELEMENT_FIRE,
            GSWE_QUALITY_MUTABLE
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_CAPRICORN,
            _("Capricorn"),
            GSWE_ELEMENT_EARTH,
            GSWE_QUALITY_CARDINAL
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_AQUARIUS,
            _("Aquarius"),
            GSWE_ELEMENT_AIR,
            GSWE_QUALITY_FIX
        );
    ADD_SIGN(gswe_sign_info_table, sign_info,
            GSWE_SIGN_PISCES,
            _("Pisces"),
            GSWE_ELEMENT_WATER,
            GSWE_QUALITY_MUTABLE
        );

    gswe_house_system_info_table = g_hash_table_new_full(
            g_direct_hash, g_direct_equal,
            NULL, (GDestroyNotify)gswe_house_system_info_unref
        );

    ADD_HOUSE_SYSTEM(gswe_house_system_info_table, house_system_info,
            GSWE_HOUSE_SYSTEM_NONE,
            0,
            _("None")
        );
    ADD_HOUSE_SYSTEM(gswe_house_system_info_table, house_system_info,
            GSWE_HOUSE_SYSTEM_PLACIDUS,
            'P',
            _("Placidus")
        );
    ADD_HOUSE_SYSTEM(gswe_house_system_info_table, house_system_info,
            GSWE_HOUSE_SYSTEM_KOCH,
            'K',
            _("Koch")
        );
    ADD_HOUSE_SYSTEM(gswe_house_system_info_table, house_system_info,
            GSWE_HOUSE_SYSTEM_EQUAL,
            'E',
            _("Equal")
        );

    gswe_aspect_info_table = g_hash_table_new_full(
            g_direct_hash, g_direct_equal,
            NULL, (GDestroyNotify)gswe_aspect_info_unref
        );

    // Note that because all aspects must be <= 180°, GSWE_ASPECT_NONE can
    // never really exist. It is provided for name fetching purposes only.
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_NONE,
            _("None"),
            360,
            4,
            FALSE,
            FALSE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_CONJUCTION,
            _("Conjuction"),
            0,
            0,
            TRUE,
            TRUE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_OPPOSITION,
            _("Opposition"),
            180,
            0,
            TRUE,
            TRUE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_TRINE,
            _("Trine"),
            120,
            0,
            TRUE,
            TRUE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_SQUARE,
            _("Square"),
            90,
            0,
            FALSE,
            TRUE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_SEXTILE,
            _("Sextile"),
            60,
            1,
            TRUE,
            TRUE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_QUINCUNX,
            _("Quincunx"),
            150,
            2,
            FALSE,
            FALSE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_SEMISEXTILE,
            _("Semi-sextile"),
            30,
            2,
            TRUE,
            FALSE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_SEMISQUARE,
            _("Semi-square"),
            45,
            2,
            FALSE,
            FALSE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_SESQUISQUARE,
            _("Sesqui-square"),
            135,
            2,
            FALSE,
            FALSE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_QUINTILE,
            _("Quintile"),
            72,
            3,
            TRUE,
            FALSE
        );
    ADD_ASPECT(gswe_aspect_info_table, aspect_info,
            GSWE_ASPECT_BIQUINTILE,
            _("Bi-quintile"),
            144,
            3,
            TRUE,
            FALSE
        );

    gswe_antiscion_axis_info_table = g_hash_table_new_full(
            g_direct_hash, g_direct_equal,
            NULL, (GDestroyNotify)gswe_antiscion_axis_info_unref
        );

    ADD_ANTISCION(gswe_antiscion_axis_info_table, antiscion_axis_info,
            gswe_sign_info_table, sign_info,
            GSWE_ANTISCION_AXIS_NONE,
            _("None"),
            GSWE_SIGN_NONE,
            0.0
        );
    ADD_ANTISCION(gswe_antiscion_axis_info_table, antiscion_axis_info,
            gswe_sign_info_table, sign_info,
            GSWE_ANTISCION_AXIS_ARIES,
            _("Aries/Libra"),
            GSWE_SIGN_ARIES,
            0.0
        );
    ADD_ANTISCION(gswe_antiscion_axis_info_table, antiscion_axis_info,
            gswe_sign_info_table, sign_info,
            GSWE_ANTISCION_AXIS_MID_TAURUS,
            _("mid Taurus/Scorpio"),
            GSWE_SIGN_TAURUS,
            15.0
        );
    ADD_ANTISCION(gswe_antiscion_axis_info_table, antiscion_axis_info,
            gswe_sign_info_table, sign_info,
            GSWE_ANTISCION_AXIS_CANCER,
            _("Cancer/Capricorn"),
            GSWE_SIGN_CANCER,
            0.0
        );
    ADD_ANTISCION(gswe_antiscion_axis_info_table, antiscion_axis_info,
            gswe_sign_info_table, sign_info,
            GSWE_ANTISCION_AXIS_MID_LEO,
            _("mid Leo/Aquarius"),
            GSWE_SIGN_LEO,
            15.0
        );

    gswe_full_moon_base_date = gswe_timestamp_new_from_gregorian_full(
            2005, 5, 8,
            3, 48, 0, 0,
            0.0
        );

    gswe_ephe_path = g_strdup(directory);
    swe_set_ephe_path(directory);
    gswe_initialized = TRUE;
}

/**
 * gswe_init:
 *
 * Initializes the SWE-GLib library. It must be called before any calculations
 * are made.
 */
void
gswe_init(void)
{
    gswe_init_with_dir(PKGDATADIR);
}

/**
 * gswe_find_planet_info_by_id:
 * @planet: a planet ID registered with SWE-GLib
 * @err: a GError
 *
 * Find the #GswePlanetInfo record registered with the id @planet.
 *
 * Since: 2.1
 */
GswePlanetInfo *
gswe_find_planet_info_by_id(GswePlanet planet, GError **err)
{
    GswePlanetInfo *ret = g_hash_table_lookup(
            gswe_planet_info_table,
            GINT_TO_POINTER(planet)
        );

    if (ret == NULL) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_PLANET,
                "Planet %d is not registered", planet
            );
    }

    return ret;
}

/**
 * gswe_find_sign_info_by_id:
 * @sign: a sign ID registered with SWE-GLib
 * @err: a GError
 *
 * Find the #GsweSignInfo record registered with the id @sign.
 *
 * Since: 2.1
 */
GsweSignInfo *
gswe_find_sign_info_by_id(GsweZodiac sign, GError **err)
{
    GsweSignInfo *ret = g_hash_table_lookup(
            gswe_sign_info_table,
            GINT_TO_POINTER(sign)
        );

    if (ret == NULL) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_SIGN,
                "Sign %d is not registered", sign
            );
    }

    return ret;
}

/**
 * gswe_find_house_system_info_by_id:
 * @house_system: a house system ID registered with SWE-GLib
 * @err: a GError
 *
 * Find the #GsweHouseSystemInfo record registered with the id @house_system.
 *
 * Since: 2.1
 */
GsweHouseSystemInfo *
gswe_find_house_system_info_by_id(GsweHouseSystem house_system, GError **err)
{
    GsweHouseSystemInfo *ret = g_hash_table_lookup(
            gswe_house_system_info_table,
            GINT_TO_POINTER(house_system)
        );

    if (ret == NULL) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_HSYS,
                "House system %d is not registered", house_system
            );
    }

    return ret;
}

/**
 * gswe_find_aspect_info_by_id:
 * @aspect: an aspect ID registered with SWE-GLib
 * @err: a GError
 *
 * Find the #GsweAspectInfo record registered with the id @aspect.
 *
 * Since: 2.1
 */
GsweAspectInfo *
gswe_find_aspect_info_by_id(GsweAspect aspect, GError **err)
{
    GsweAspectInfo *ret = g_hash_table_lookup(
            gswe_aspect_info_table,
            GINT_TO_POINTER(aspect)
        );

    if (ret == NULL) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_ASPECT,
                "Aspect system %d is not registered", aspect
            );
    }

    return ret;
}

/**
 * gswe_find_antiscion_axis_info_by_id:
 * @antiscion_axis: an antiscion axis ID registered with SWE-GLib
 * @err: a GError
 *
 * Find the #GsweAntiscionAxisInfo record registered with the id
 * @antiscion_axis.
 *
 * Since: 2.1
 */
GsweAntiscionAxisInfo *
gswe_find_antiscion_axis_info_by_id(
        GsweAntiscionAxis antiscion_axis,
        GError **err)
{
    GsweAntiscionAxisInfo *ret = g_hash_table_lookup(
            gswe_antiscion_axis_info_table,
            GINT_TO_POINTER(antiscion_axis)
        );

    if (ret == NULL) {
        g_set_error(
                err,
                GSWE_ERROR, GSWE_ERROR_UNKNOWN_ANTISCION_AXIS,
                "Antiscion axis system %d is not registered", antiscion_axis
            );
    }

    return ret;
}

/**
 * gswe_all_house_systems:
 *
 * Returns: (element-type GsweHouseSystemInfo) (transfer container):
 * All #GsweHouseSystemInfo registered with SWE-GLib. The elements of
 * this list should not be modified nor freed. The list is only valid
 * until a new house system is registered.
 *
 * Since: 2.1.0
 */
GList *
gswe_all_house_systems(void)
{
    return g_hash_table_get_values(gswe_house_system_info_table);
}

/**
 * gswe_all_planets:
 *
 * Returns: (element-type GswePlanetInfo) (transfer container): All
 * #GswePlanetInfo registered with SWE-GLib. The elements of this list
 * should not be modified nor freed. The list is only valid until a
 * new planet is registered.
 *
 * Since: 2.1.0
 */
GList *
gswe_all_planets(void)
{
    return g_hash_table_get_values(gswe_planet_info_table);
}

/**
 * gswe_all_aspects:
 *
 * Returns: (element-type GsweAspectInfo) (transfer container): All
 * #GsweAspectInfo registered with SWE-GLib. The elements of this list
 * should not be modified nor freed. The list is only valid until a
 * new aspect is registered.
 *
 * Since: 2.1.0
 */
GList *
gswe_all_aspects(void)
{
    return g_hash_table_get_values(gswe_aspect_info_table);
}

/**
 * gswe_all_antiscion_axes:
 *
 * Returns: (element-type GsweAntiscionAxisInfo) (transfer container):
 * All #GsweAntiscionAxisInfo registered with SWE-GLib. The elements
 * of this list should not be modified nor freed. The list is only
 * valid until a new antiscion axis is registered.
 *
 * Since: 2.1.0
 */
GList *
gswe_all_antiscion_axes(void)
{
    return g_hash_table_get_values(gswe_antiscion_axis_info_table);
}
