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

gboolean gswe_initialized = FALSE;
gchar *gswe_ephe_path = NULL;
GHashTable *gswe_planet_info_table;
GHashTable *gswe_sign_info_table;
GHashTable *gswe_house_system_info_table;
GHashTable *gswe_aspect_info_table;
GHashTable *gswe_antiscion_axis_info_table;
GsweTimestamp *gswe_full_moon_base_date;

#define ADD_PLANET(ht, v, i, s, r, n, o, h, dom1, dom2, exi1, exi2, exa, fal) (v) = g_new0(GswePlanetInfo, 1); \
                                                                              (v)->planet = (i); \
                                                                              (v)->sweph_id = (s); \
                                                                              (v)->real_body = (r); \
                                                                              (v)->orb = (o); \
                                                                              (v)->name = g_strdup(n); \
                                                                              (v)->points = (h); \
                                                                              (v)->domicile_sign_1 = (dom1); \
                                                                              (v)->domicile_sign_2 = (dom2); \
                                                                              (v)->exile_sign_1 = (exi1); \
                                                                              (v)->exile_sign_2 = (exi2); \
                                                                              (v)->exalted_sign = (exa); \
                                                                              (v)->fall_sign = (fal); \
                                                                              g_hash_table_replace((ht), GINT_TO_POINTER(i), (v));

#define ADD_SIGN(ht, v, s, n, e, q) (v) = g_new0(GsweSignInfo, 1); \
                                    (v)->sign_id = (s); \
                                    (v)->name = g_strdup(n); \
                                    (v)->element = (e); \
                                    (v)->quality = (q); \
                                    g_hash_table_replace((ht), GINT_TO_POINTER(s), (v));

#define ADD_HOUSE_SYSTEM(ht, v, i, s, n) (v) = g_new0(GsweHouseSystemInfo, 1); \
                                         (v)->system = i; \
                                         (v)->sweph_id = s; \
                                         (v)->name = g_strdup(n); \
                                         g_hash_table_replace((ht), GINT_TO_POINTER(i), (v));

#define ADD_ASPECT(ht, v, i, n, s, o, h, m) (v) = g_new0(GsweAspectInfo, 1); \
                                            (v)->aspect = (i); \
                                            (v)->name = g_strdup(n); \
                                            (v)->size = (s); \
                                            (v)->orb_modifier = (o); \
                                            (v)->harmonic = (h); \
                                            (v)->major = (m); \
                                            g_hash_table_replace((ht), GINT_TO_POINTER(i), (v));

#define ADD_ANTISCION(ht, v, hts, vs, i, n, s, m) (v) = g_new0(GsweAntiscionAxisInfo, 1); \
                                               (vs) = g_hash_table_lookup((hts), GINT_TO_POINTER(i)); \
                                               (v)->axis_id = (i); \
                                               (v)->start_sign = (vs); \
                                               (v)->name = g_strdup(n); \
                                               (v)->middle_axis = m; \
                                               g_hash_table_replace((ht), GINT_TO_POINTER(i), (v));
void
gswe_free_planet_info(gpointer planet_info)
{
    g_free(((GswePlanetInfo *)planet_info)->name);
    g_free(planet_info);
}

void
gswe_free_sign_info(gpointer sign_info)
{
    g_free(((GsweSignInfo *)sign_info)->name);
    g_free(sign_info);
}

void
gswe_free_house_system_info(gpointer house_system_info)
{
    g_free(((GsweHouseSystemInfo *)house_system_info)->name);
    g_free(house_system_info);
}

void
gswe_free_aspect_info(gpointer aspect_info)
{
    g_free(((GsweAspectInfo *)aspect_info)->name);
    g_free(aspect_info);
}

void
gswe_free_antiscion_axis_info(GsweAntiscionAxisInfo *antiscion_axis_info)
{
    g_free(antiscion_axis_info->name);
    g_free(antiscion_axis_info);
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
    GswePlanetInfo *planet_info;
    GsweSignInfo *sign_info;
    GsweHouseSystemInfo *house_system_info;
    GsweAspectInfo *aspect_info;
    GsweAntiscionAxisInfo *antiscion_axis_info;

    bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");

    gswe_planet_info_table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, gswe_free_planet_info);

    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_SUN,         SE_SUN,       TRUE,  _("Sun"),                 13.0, 2, GSWE_SIGN_LEO,         GSWE_SIGN_NONE,     GSWE_SIGN_AQUARIUS,    GSWE_SIGN_NONE,   GSWE_SIGN_ARIES,     GSWE_SIGN_LIBRA);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_MOON,        SE_MOON,      TRUE,  _("Moon"),                9.0,  2, GSWE_SIGN_CANCER,      GSWE_SIGN_NONE,     GSWE_SIGN_CAPRICORN,   GSWE_SIGN_NONE,   GSWE_SIGN_TAURUS,    GSWE_SIGN_SCORPIO);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_MERCURY,     SE_MERCURY,   TRUE,  _("Mercury"),             7.0,  2, GSWE_SIGN_GEMINI,      GSWE_SIGN_VIRGO,    GSWE_SIGN_SAGITTARIUS, GSWE_SIGN_PISCES, GSWE_SIGN_VIRGO,     GSWE_SIGN_PISCES);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_VENUS,       SE_VENUS,     TRUE,  _("Venus"),               7.0,  1, GSWE_SIGN_TAURUS,      GSWE_SIGN_LIBRA,    GSWE_SIGN_SCORPIO,     GSWE_SIGN_ARIES,  GSWE_SIGN_PISCES,    GSWE_SIGN_VIRGO);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_MARS,        SE_MARS,      TRUE,  _("Mars"),                7.0,  1, GSWE_SIGN_ARIES,       GSWE_SIGN_SCORPIO,  GSWE_SIGN_LIBRA,       GSWE_SIGN_TAURUS, GSWE_SIGN_CAPRICORN, GSWE_SIGN_CANCER);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_JUPITER,     SE_JUPITER,   TRUE,  _("Jupiter"),             9.0,  1, GSWE_SIGN_SAGITTARIUS, GSWE_SIGN_PISCES,   GSWE_SIGN_GEMINI,      GSWE_SIGN_VIRGO,  GSWE_SIGN_CANCER,    GSWE_SIGN_CAPRICORN);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_SATURN,      SE_SATURN,    TRUE,  _("Saturn"),              7.0,  1, GSWE_SIGN_CAPRICORN,   GSWE_SIGN_AQUARIUS, GSWE_SIGN_CANCER,      GSWE_SIGN_LEO,    GSWE_SIGN_LIBRA,     GSWE_SIGN_ARIES);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_URANUS,      SE_URANUS,    TRUE,  _("Uranus"),              5.0,  1, GSWE_SIGN_AQUARIUS,    GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_NEPTUNE,     SE_NEPTUNE,   TRUE,  _("Neptune"),             5.0,  1, GSWE_SIGN_PISCES,      GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_PLUTO,       SE_PLUTO,     TRUE,  _("Pluto"),               3.0,  1, GSWE_SIGN_SCORPIO,     GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_CHIRON,      SE_CHIRON,    TRUE,  _("Chiron"),              2.0,  0, GSWE_SIGN_NONE,        GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_CERES,       SE_CERES,     TRUE,  _("Ceres"),               2.0,  0, GSWE_SIGN_NONE,        GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_PALLAS,      SE_PALLAS,    TRUE,  _("Pallas"),              2.0,  0, GSWE_SIGN_NONE,        GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_JUNO,        SE_JUNO,      TRUE,  _("Juno"),                2.0,  0, GSWE_SIGN_NONE,        GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_VESTA,       SE_VESTA,     TRUE,  _("Vesta"),               2.0,  0, GSWE_SIGN_NONE,        GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_MOON_NODE,   SE_MEAN_NODE, TRUE,  _("Ascending Moon Node"), 2.0,  1, GSWE_SIGN_NONE,        GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_MOON_APOGEE, SE_MEAN_APOG, TRUE,  _("Dark Moon"),           2.0,  0, GSWE_SIGN_NONE,        GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_ASCENDENT,   -1,           FALSE, _("Ascendent"),           9.0,  2, GSWE_SIGN_NONE,        GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_MC,          -1,           FALSE, _("Midheaven"),           5.0,  1, GSWE_SIGN_NONE,        GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);
    ADD_PLANET(gswe_planet_info_table, planet_info, GSWE_PLANET_VERTEX,      -1,           FALSE, _("Vertex"),              2.0,  0, GSWE_SIGN_NONE,        GSWE_SIGN_NONE,     GSWE_SIGN_NONE,        GSWE_SIGN_NONE,   GSWE_SIGN_NONE,      GSWE_SIGN_NONE);

    gswe_sign_info_table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, gswe_free_sign_info);

    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_ARIES,       _("Aries"),       GSWE_ELEMENT_FIRE,  GSWE_QUALITY_CARDINAL);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_TAURUS,      _("Taurus"),      GSWE_ELEMENT_EARTH, GSWE_QUALITY_FIX);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_GEMINI,      _("Gemini"),      GSWE_ELEMENT_AIR,   GSWE_QUALITY_MUTABLE);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_CANCER,      _("Cancer"),      GSWE_ELEMENT_WATER, GSWE_QUALITY_CARDINAL);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_LEO,         _("Leo"),         GSWE_ELEMENT_FIRE,  GSWE_QUALITY_FIX);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_VIRGO,       _("Virgo"),       GSWE_ELEMENT_EARTH, GSWE_QUALITY_MUTABLE);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_LIBRA,       _("Libra"),       GSWE_ELEMENT_AIR,   GSWE_QUALITY_CARDINAL);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_SCORPIO,     _("Scorpio"),     GSWE_ELEMENT_WATER, GSWE_QUALITY_FIX);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_SAGITTARIUS, _("Sagittarius"), GSWE_ELEMENT_FIRE,  GSWE_QUALITY_MUTABLE);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_CAPRICORN,   _("Capricorn"),   GSWE_ELEMENT_EARTH, GSWE_QUALITY_CARDINAL);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_AQUARIUS,    _("Aquarius"),    GSWE_ELEMENT_AIR,   GSWE_QUALITY_FIX);
    ADD_SIGN(gswe_sign_info_table, sign_info, GSWE_SIGN_PISCES,      _("Pisces"),      GSWE_ELEMENT_WATER, GSWE_QUALITY_MUTABLE);

    gswe_house_system_info_table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, gswe_free_house_system_info);

    ADD_HOUSE_SYSTEM(gswe_house_system_info_table, house_system_info, GSWE_HOUSE_SYSTEM_NONE,     0,   _("None"));
    ADD_HOUSE_SYSTEM(gswe_house_system_info_table, house_system_info, GSWE_HOUSE_SYSTEM_PLACIDUS, 'P', _("Placidus"));
    ADD_HOUSE_SYSTEM(gswe_house_system_info_table, house_system_info, GSWE_HOUSE_SYSTEM_KOCH,     'K', _("Koch"));
    ADD_HOUSE_SYSTEM(gswe_house_system_info_table, house_system_info, GSWE_HOUSE_SISTEM_EQUAL,    'E', _("Equal"));

    gswe_aspect_info_table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, gswe_free_aspect_info);

    // Note that because all aspects must be <= 180°, GSWE_ASPECT_NONE can
    // never really exist. It is provided for name fetching purposes only.
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_NONE,         _("None"),          360, 4, FALSE, FALSE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_CONJUCTION,   _("Conjuction"),    0,   0, TRUE,  TRUE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_OPPOSITION,   _("Opposition"),    180, 0, TRUE,  TRUE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_TRINE,        _("Trine"),         120, 0, TRUE,  TRUE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_SQUARE,       _("Square"),        90,  0, FALSE, TRUE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_SEXTILE,      _("Sextile"),       60,  1, TRUE,  TRUE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_QUINCUNX,     _("Quincunx"),      150, 2, FALSE, FALSE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_SEMISEXTILE,  _("Semi-sextile"),  30,  2, TRUE,  FALSE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_SEMISQUARE,   _("Semi-square"),   45,  2, FALSE, FALSE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_SESQUISQUARE, _("Sesqui-square"), 135, 2, FALSE, FALSE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_QUINTILE,     _("Quintile"),      72,  3, TRUE,  FALSE);
    ADD_ASPECT(gswe_aspect_info_table, aspect_info, GSWE_ASPECT_BIQUINTILE,   _("Bi-quintile"),   144, 3, TRUE,  FALSE);

    gswe_antiscion_axis_info_table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)gswe_free_antiscion_axis_info);

    ADD_ANTISCION(gswe_antiscion_axis_info_table, antiscion_axis_info, gswe_sign_info_table, sign_info, GSWE_ANTISCION_AXIS_NONE,       _("None"),               GSWE_SIGN_NONE,   FALSE);
    ADD_ANTISCION(gswe_antiscion_axis_info_table, antiscion_axis_info, gswe_sign_info_table, sign_info, GSWE_ANTISCION_AXIS_ARIES,      _("Aries/Libra"),        GSWE_SIGN_ARIES,  FALSE);
    ADD_ANTISCION(gswe_antiscion_axis_info_table, antiscion_axis_info, gswe_sign_info_table, sign_info, GSWE_ANTISCION_AXIS_MID_TAURUS, _("mid Taurus/Scorpio"), GSWE_SIGN_TAURUS, TRUE);
    ADD_ANTISCION(gswe_antiscion_axis_info_table, antiscion_axis_info, gswe_sign_info_table, sign_info, GSWE_ANTISCION_AXIS_CANCER,     _("Cancer/Capricorn"),   GSWE_SIGN_CANCER, FALSE);
    ADD_ANTISCION(gswe_antiscion_axis_info_table, antiscion_axis_info, gswe_sign_info_table, sign_info, GSWE_ANTISCION_AXIS_MID_LEO,    _("mid Leo/Aquarius"),   GSWE_SIGN_LEO,    TRUE);

    gswe_full_moon_base_date = gswe_timestamp_new_from_gregorian_full(2005, 5, 8, 3, 48, 0, 0, 0.0);

    gswe_ephe_path = g_strdup(PKGDATADIR);
    swe_set_ephe_path(PKGDATADIR);
    gswe_initialized = TRUE;
}

static GswePlanetInfo *
gswe_planet_info_copy(GswePlanetInfo *planet_info)
{
    GswePlanetInfo *ret = g_new0(GswePlanetInfo, 1);

    ret->planet = planet_info->planet;
    ret->sweph_id = planet_info->sweph_id;
    ret->real_body = planet_info->real_body;
    ret->orb = planet_info->orb;
    ret->name = g_strdup(planet_info->name);
    ret->points = planet_info->points;
    ret->domicile_sign_1 = planet_info->domicile_sign_1;
    ret->domicile_sign_2 = planet_info->domicile_sign_2;
    ret->exile_sign_1 = planet_info->exile_sign_1;
    ret->exile_sign_2 = planet_info->exile_sign_2;
    ret->exalted_sign = planet_info->exalted_sign;
    ret->fall_sign = planet_info->fall_sign;

    return ret;
}

static void
gswe_planet_info_free(GswePlanetInfo *planet_info)
{
    g_free(planet_info->name);
    g_free(planet_info);
}

G_DEFINE_BOXED_TYPE(GswePlanetInfo, gswe_planet_info, (GBoxedCopyFunc)gswe_planet_info_copy, (GBoxedFreeFunc)gswe_planet_info_free);

static GsweSignInfo *
gswe_sign_info_copy(GsweSignInfo *sign_info)
{
    GsweSignInfo *ret = g_new0(GsweSignInfo, 1);

    ret->sign_id = sign_info->sign_id;
    ret->name = g_strdup(sign_info->name);
    ret->element = sign_info->element;
    ret->quality = sign_info->quality;

    return ret;
}

static void
gswe_sign_info_free(GsweSignInfo *sign_info)
{
    g_free(sign_info->name);
    g_free(sign_info);
}

G_DEFINE_BOXED_TYPE(GsweSignInfo, gswe_sign_info, (GBoxedCopyFunc)gswe_sign_info_copy, (GBoxedFreeFunc)gswe_sign_info_free);
