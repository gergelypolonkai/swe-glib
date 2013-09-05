#ifndef __SWE_GLIB_GSWE_PLANETS_H__
#define __SWE_GLIB_GSWE_PLANETS_H__

#include <glib.h>

/**
 * GswePlanet:
 * @GSWE_PLANET_NONE: no planet
 * @GSWE_PLANET_SUN: the Sun
 * @GSWE_PLANET_MOON: the Moon
 * @GSWE_PLANET_MERCURY: planet Mercury
 * @GSWE_PLANET_VENUS: planet Venus
 * @GSWE_PLANET_EARTH: planet Earth
 * @GSWE_PLANET_MARS: planet Mars
 * @GSWE_PLANET_JUPITER: planet Jupiter
 * @GSWE_PLANET_SATURN: planet Saturn
 * @GSWE_PLANET_URANUS: planet Uranus
 * @GSWE_PLANET_NEPTUNE: planet Neptune
 * @GSWE_PLANET_PLUTO: planet Pluto
 * @GSWE_PLANET_CHIRON: dwarf planet Chiron
 * @GSWE_PLANET_CERES: dwarf planet Ceres
 * @GSWE_PLANET_PALLAS: dwarf planet Pallas
 * @GSWE_PLANET_JUNO: dwarf planet Juno
 * @GSWE_PLANET_VESTA: dwarf planet Vesta
 * @GSWE_PLANET_MOON_NODE: the mean ascending (north) Moon node
 * @GSWE_PLANET_MOON_APOGEE: the mean Moon apogee (sometimes called Dark Moon,
 *                           or Lilith)
 * @GSWE_PLANET_ASCENDENT: the ascendent
 * @GSWE_PLANET_MC: midheaven (Medium Coeli)
 * @GSWE_PLANET_VERTEX: the Vertex (the point where the ecliptic meats the
 *                      primal vertical)
 */
typedef enum {
    GSWE_PLANET_NONE,
    GSWE_PLANET_SUN,
    GSWE_PLANET_MOON,
    GSWE_PLANET_MERCURY,
    GSWE_PLANET_VENUS,
    GSWE_PLANET_EARTH,
    GSWE_PLANET_MARS,
    GSWE_PLANET_JUPITER,
    GSWE_PLANET_SATURN,
    GSWE_PLANET_URANUS,
    GSWE_PLANET_NEPTUNE,
    GSWE_PLANET_PLUTO,
    GSWE_PLANET_CHIRON,
    GSWE_PLANET_CERES,
    GSWE_PLANET_PALLAS,
    GSWE_PLANET_JUNO,
    GSWE_PLANET_VESTA,
    GSWE_PLANET_MOON_NODE,
    GSWE_PLANET_MOON_APOGEE,
    GSWE_PLANET_ASCENDENT,
    GSWE_PLANET_MC,
    GSWE_PLANET_VERTEX
} GswePlanet;

/**
 * GsweZodiac:
 * @GSWE_SIGN_NONE: no sign
 * @GSWE_SIGN_ARIES: the Aries sign (Ram)
 * @GSWE_SIGN_TAURUS: the Taurus sign (Bull)
 * @GSWE_SIGN_GEMINI: the Gemini sign (Twins)
 * @GSWE_SIGN_CANCER: the Cancer sign (Crab)
 * @GSWE_SIGN_LEO: the Leo sign (Lion)
 * @GSWE_SIGN_VIRGO: the Virgo sign (Maid)
 * @GSWE_SIGN_LIBRA: the Libra sign (Scales)
 * @GSWE_SIGN_SCORPIO: the Scorpio sign (Scorpion)
 * @GSWE_SIGN_SAGITTARIUS: the Sagittarius sign (Archer)
 * @GSWE_SIGN_CAPRICORN: the Capricorn sign (Goat)
 * @GSWE_SIGN_AQUARIUS: the Aquarius sign (Water Bearer)
 * @GSWE_SIGN_PISCES: the Pisces sign (Fish)
 */
typedef enum {
    GSWE_SIGN_NONE,
    GSWE_SIGN_ARIES,
    GSWE_SIGN_TAURUS,
    GSWE_SIGN_GEMINI,
    GSWE_SIGN_CANCER,
    GSWE_SIGN_LEO,
    GSWE_SIGN_VIRGO,
    GSWE_SIGN_LIBRA,
    GSWE_SIGN_SCORPIO,
    GSWE_SIGN_SAGITTARIUS,
    GSWE_SIGN_CAPRICORN,
    GSWE_SIGN_AQUARIUS,
    GSWE_SIGN_PISCES
} GsweZodiac;

typedef enum {
    GSWE_ASPECT_NONE,
    GSWE_ASPECT_CONJUCTION,
    GSWE_ASPECT_SEXTILE,
    GSWE_ASPECT_SQUARE,
    GSWE_ASPECT_TRINE,
    GSWE_ASPECT_OPPOSITION,
    GSWE_ASPECT_SEMISEXTILE,
    GSWE_ASPECT_SEMISQUARE,
    GSWE_ASPECT_QUINTILE,
    GSWE_ASPECT_SESQUISQUARE,
    GSWE_ASPECT_BIQUINTILE,
    GSWE_ASPECT_QUINCUNX
} GsweAspect;

typedef enum {
    GSWE_MIRROR_NONE,
    GSWE_MIRROR_ARIES,
    GSWE_MIRROR_MID_TAURUS,
    GSWE_MIRROR_CANCER,
    GSWE_MIRROR_MID_LEO
} GsweMirror;

typedef enum {
    GSWE_ELEMENT_NONE,
    GSWE_ELEMENT_FIRE,
    GSWE_ELEMENT_EARTH,
    GSWE_ELEMENT_AIR,
    GSWE_ELEMENT_WATER
} GsweElement;

typedef enum {
    GSWE_QUALITY_NONE,
    GSWE_QUALITY_CARDINAL,
    GSWE_QUALITY_FIX,
    GSWE_QUALITY_MUTABLE
} GsweQuality;

typedef enum {
    GSWE_HOUSE_SYSTEM_NONE,
    GSWE_HOUSE_SYSTEM_PLACIDUS,
    GSWE_HOUSE_SYSTEM_KOCH,
    GSWE_HOUSE_SISTEM_EQUAL
} GsweHouseSystem;

typedef enum {
    GSWE_MOON_PHASE_NEW,
    GSWE_MOON_PHASE_WAXING_CRESCENT,
    GSWE_MOON_PHASE_WAXING_HALF,
    GSWE_MOON_PHASE_WAXING_GIBBOUS,
    GSWE_MOON_PHASE_FULL,
    GSWE_MOON_PHASE_WANING_GIBBOUS,
    GSWE_MOON_PHASE_WANING_HALF,
    GSWE_MOON_PHASE_WANING_CRESCENT,
    GSWE_MOON_PHASE_DARK
} GsweMoonPhase;

/**
 * GswePlanetInfo:
 * @planet:          the planet ID
 * @sweph_id:        the planet ID according to the Swiss Ephemeris libarary
 *                   (or -1, if the planet has no such ID)
 * @real_body:       TRUE if the planet is a "real" celestial body on the sky.
 *                   Please note that this will be true for Dark Moon (Lilith).
 *                   Everything that has a planet ID in Swiss Ephemeris is
 *                   treated as a real celestial body.
 * @orb:             the planet's “personal” orb
 * @name:            the planet's name
 * @points:          the value this planet counts in the element/quality points
 *                   table
 * @domicile_sign_1: the first sign in which the planet is domicile
 * @domicile_sign_2: the second sign in which the planet is domicile
 * @exile_sign_1:    the first sign in which the planet is in exile
 * @exile_sign_2:    the second sign in which the planet is in exile
 * @exalted_sign:    the sign in which the planet is exalted
 * @fall_sign:       the sign in which the planet is in fall
 */
typedef struct {
    GswePlanet planet;
    gint sweph_id;
    gboolean real_body;
    gdouble orb;
    gchar *name;
    gint points;
    GsweZodiac domicile_sign_1;
    GsweZodiac domicile_sign_2;
    GsweZodiac exile_sign_1;
    GsweZodiac exile_sign_2;
    GsweZodiac exalted_sign;
    GsweZodiac fall_sign;
} GswePlanetInfo;

typedef struct {
    GsweZodiac sign_id;
    gchar *name;
    GsweElement element;
    GsweQuality quality;
} GsweSignInfo;

/**
 * GsweHouseSystemInfo:
 * @system: the house system's ID
 * @sweph_id: the character value that represents this house system in the Swiss Ephemeris library
 * @name: the name of this house system
 */
typedef struct {
    GsweHouseSystem system;
    gchar sweph_id;
    gchar *name;
} GsweHouseSystemInfo;

typedef struct {
    GsweAspect aspect;
    gchar *name;
    guint size;
    guint orb_modifier;
    gboolean harmonic;
    gboolean major;
} GsweAspectInfo;

typedef struct {
    GsweMirror mirror_id;
    GsweSignInfo *start_sign;
    gchar *name;
    gboolean middle_axis;
} GsweMirrorInfo;

#endif /* __SWE_GLIB_GSWE_PLANETS_H__ */

