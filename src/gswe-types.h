/* gswe-types.h - Basic types of SWE-GLib
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
#ifndef __SWE_GLIB_GSWE_TYPES_H__
#define __SWE_GLIB_GSWE_TYPES_H__

#include <glib.h>
#include <glib-object.h>

/**
 * SECTION:gswe-types
 * @short_description: Base types of SWE-GLib
 * @title: Base types
 * @stability: Stable
 * @include: swe-glib/swe-glib.h
 *
 * These are the base types used throughout SWE-GLib.
 */

/**
 * GswePlanet:
 * @GSWE_PLANET_NONE: no planet
 * @GSWE_PLANET_ASCENDANT: the ascendant
 * @GSWE_PLANET_DESCENDANT: the descendant
 * @GSWE_PLANET_MC: midheaven (Medium Coeli)
 * @GSWE_PLANET_IC: Immum Coeli
 * @GSWE_PLANET_VERTEX: the Vertex (the point where the ecliptic meats the
 *                      primal vertical)
 * @GSWE_PLANET_ANTIVERTEX: the Antivertex (the point opposing the Vertex)
 * @GSWE_PLANET_MOON_NODE: the mean ascending (north) Moon node
 * @GSWE_PLANET_MOON_SOUTH_NODE: the mean descending (south) Moon node
 * @GSWE_PLANET_MOON_APOGEE: the mean Moon apogee (sometimes called Dark Moon,
 *                           or Lilith)
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
 * @GSWE_PLANET_PHOLUS: asteroid Pholus
 * @GSWE_PLANET_NESSUS: asteroid Nessus
 * @GSWE_PLANET_CHARIKLO: asteroid Chariklo
 * @GSWE_PLANET_SEDNA: dwarf planet Sedna
 * @GSWE_PLANET_ERIS: dwarf planet Eris
 * @GSWE_PLANET_DEJANIRA: dwarf planet Dejanira
 * @GSWE_PLANET_CIRCE: asteroid Circe
 * @GSWE_PLANET_ORCUS: asteroid Orcus
 * @GSWE_PLANET_ASBOLUS: asteroid Asbolus
 * @GSWE_PLANET_HYGIEA: asteroid Hygiea
 *
 * This enum holds the planet identifiers known by SWE-GLib.
 */
typedef enum {
    /* Theoretical/non-existing points */
    GSWE_PLANET_NONE = 0,
    GSWE_PLANET_ASCENDANT,
    GSWE_PLANET_MC,
    GSWE_PLANET_VERTEX,
    GSWE_PLANET_MOON_NODE,
    GSWE_PLANET_MOON_APOGEE,
    GSWE_PLANET_MOON_SOUTH_NODE,
    GSWE_PLANET_DESCENDANT,
    GSWE_PLANET_IC,
    GSWE_PLANET_ANTIVERTEX,

    /* Actual astrological planets */
    GSWE_PLANET_SUN = 11,
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
    /* Dwarves and asteroids */
    GSWE_PLANET_CHIRON = 101, /* Included in ephemerides files */
    GSWE_PLANET_CERES,        /* Included in ephemerides files */
    GSWE_PLANET_PALLAS,       /* Included in ephemerides files */
    GSWE_PLANET_JUNO,         /* Included in ephemerides files */
    GSWE_PLANET_VESTA,        /* Included in ephemerides files */
    GSWE_PLANET_PHOLUS,       /* Included in ephemerides files */
    GSWE_PLANET_NESSUS,       /* 7066 */
    GSWE_PLANET_CHARIKLO,     /* 10199 */
    GSWE_PLANET_SEDNA,        /* 90377 */
    GSWE_PLANET_ERIS,         /* 136199 */
    GSWE_PLANET_DEJANIRA,     /* 157 */
    GSWE_PLANET_CIRCE,        /* 34 */
    GSWE_PLANET_ORCUS,        /* 90482 */
    GSWE_PLANET_ASBOLUS,      /* 8405 */
    GSWE_PLANET_HYGIEA        /* 10 */
} GswePlanet;

/* Moon Apogee in astrology is often referred to as the Dark Moon, or Lilith */
#define GSWE_PLANET_LILITH GSWE_PLANET_MOON_APOGEE

/**
 * GSWE_PLANET_OFFSET_VIRTUAL_NODES:
 *
 * The offset in #GswePlanet for virtual nodes like the ascendant or vertex.
 * This is for consistency only, I don’t think anyone would need it.
 */
#define GSWE_PLANET_OFFSET_VIRTUAL_NODES 0

/**
 * GSWE_PLANET_OFFSET_PLANETS:
 *
 * The offset in #GswePlanet for real planets in the Solar System. These are
 * the objects classified as planets (including Pluto).
 */
#define GSWE_PLANET_OFFSET_PLANETS 10

/**
 * GSWE_PLANET_OFFSET_ASTEROIDS:
 *
 * The offset in #GswePlanet for asteroids and dwarf planets.
 */
#define GSWE_PLANET_OFFSET_ASTEROIDS 100

/**
 * GSWE_PLANET_OFFSET_CUSTOM:
 *
 * The offset in #GswePlanet for custom planets. This will be used to register
 * custom planets later.
 */
#define GSWE_PLANET_OFFSET_CUSTOM 10000

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
 *
 * The zodiac signs known by SWE-GLib by default.
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

/**
 * GsweAspect:
 * @GSWE_ASPECT_NONE: no aspect
 * @GSWE_ASPECT_CONJUCTION: conjuction (0°)
 * @GSWE_ASPECT_SEXTILE: sextile (60°)
 * @GSWE_ASPECT_SQUARE: square (or quadrat; 90°)
 * @GSWE_ASPECT_TRINE: trine (or trigon; 120°)
 * @GSWE_ASPECT_OPPOSITION: opposition (180°)
 * @GSWE_ASPECT_SEMISEXTILE: semi-sextile (30°)
 * @GSWE_ASPECT_SEMISQUARE: semi-square (45°)
 * @GSWE_ASPECT_QUINTILE: quintile (72°)
 * @GSWE_ASPECT_SESQUISQUARE: sesqui-square (135°)
 * @GSWE_ASPECT_BIQUINTILE: bi-quintile (144°)
 * @GSWE_ASPECT_QUINCUNX: quincunx (150°)
 *
 * The aspects known by SWE-GLib by default.
 */
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

/**
 * GsweAntiscionAxis:
 * @GSWE_ANTISCION_AXIS_NONE: no mirror
 * @GSWE_ANTISCION_AXIS_ARIES: mirror on the Aries/Libra (0°-180°) axis
 * @GSWE_ANTISCION_AXIS_MID_TAURUS: mirror on the middle of Taurus/Scorpio
 *                                  (45°-225°) axis
 * @GSWE_ANTISCION_AXIS_CANCER: mirror on the Cancer/Capricorn (90°-270°) axis
 * @GSWE_ANTISCION_AXIS_MID_LEO: mirror on the middle of Leo/Aquarius
 *                               (135°-315°) axis
 *
 * The antiscion axes known by SWE-GLib by default.
 */
typedef enum {
    GSWE_ANTISCION_AXIS_NONE,
    GSWE_ANTISCION_AXIS_ARIES,
    GSWE_ANTISCION_AXIS_MID_TAURUS,
    GSWE_ANTISCION_AXIS_CANCER,
    GSWE_ANTISCION_AXIS_MID_LEO
} GsweAntiscionAxis;

/**
 * GsweElement:
 * @GSWE_ELEMENT_NONE: no element
 * @GSWE_ELEMENT_FIRE: the Fire element
 * @GSWE_ELEMENT_EARTH: the Earth element
 * @GSWE_ELEMENT_AIR: the Air element
 * @GSWE_ELEMENT_WATER: the Water element
 *
 * The elements as known by the SWE-GLib library.
 */
typedef enum {
    GSWE_ELEMENT_NONE,
    GSWE_ELEMENT_FIRE,
    GSWE_ELEMENT_EARTH,
    GSWE_ELEMENT_AIR,
    GSWE_ELEMENT_WATER
} GsweElement;

/**
 * GsweQuality:
 * @GSWE_QUALITY_NONE: no quality
 * @GSWE_QUALITY_CARDINAL: Cardinal quality
 * @GSWE_QUALITY_FIX: Fix quality
 * @GSWE_QUALITY_MUTABLE: Mutable quality
 *
 * The qualities as known by the SWE-GLib library.
 */
typedef enum {
    GSWE_QUALITY_NONE,
    GSWE_QUALITY_CARDINAL,
    GSWE_QUALITY_FIX,
    GSWE_QUALITY_MUTABLE
} GsweQuality;

/**
 * GsweHouseSystem:
 * @GSWE_HOUSE_SYSTEM_NONE: no house system
 * @GSWE_HOUSE_SYSTEM_PLACIDUS: Placidus house system
 * @GSWE_HOUSE_SYSTEM_KOCH: Koch house system
 * @GSWE_HOUSE_SYSTEM_EQUAL: Equal house system
 *
 * The house systems currently known by SWE-GLib.
 */
typedef enum {
    GSWE_HOUSE_SYSTEM_NONE,
    GSWE_HOUSE_SYSTEM_PLACIDUS,
    GSWE_HOUSE_SYSTEM_KOCH,
    GSWE_HOUSE_SYSTEM_EQUAL
} GsweHouseSystem;

/**
 * GsweMoonPhase:
 * @GSWE_MOON_PHASE_NONE: Moon phase is not defined
 * @GSWE_MOON_PHASE_NEW: New Moon
 * @GSWE_MOON_PHASE_WAXING_CRESCENT: Waxing crescent Moon
 * @GSWE_MOON_PHASE_WAXING_HALF: First half
 * @GSWE_MOON_PHASE_WAXING_GIBBOUS: Waxing gibbous Moon
 * @GSWE_MOON_PHASE_FULL: Full Moon
 * @GSWE_MOON_PHASE_WANING_GIBBOUS: Waning gibbous Moon
 * @GSWE_MOON_PHASE_WANING_HALF: Second Half
 * @GSWE_MOON_PHASE_WANING_CRESCENT: Waning crescent Moon
 * @GSWE_MOON_PHASE_DARK: Dark Moon
 *
 * The phases of the Moon.
 */
typedef enum {
    GSWE_MOON_PHASE_NONE,
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
 * GsweTimestampValidityFlags:
 * @GSWE_VALID_NONE: No valid timestamp
 * @GSWE_VALID_GREGORIAN: Gregorian timestamp is valid
 * @GSWE_VALID_JULIAN_DAY: Julian Day is valid
 *
 * Flags to show the valid values in a #GsweTimestamp
 */
typedef enum {
    GSWE_VALID_NONE       = 0,
    GSWE_VALID_GREGORIAN  = (1 << 0),
    GSWE_VALID_JULIAN_DAY = (1 << 1)
} GsweTimestampValidityFlags;

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

GType gswe_coordinates_get_type(void);
#define GSWE_TYPE_COORDINATES (gswe_coordinates_get_type())

#endif /* __SWE_GLIB_GSWE_TYPES_H__ */
