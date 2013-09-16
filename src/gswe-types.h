/* gswe-types.h - Basic types of SWE-GLib
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
#ifndef __SWE_GLIB_GSWE_PLANETS_H__
#define __SWE_GLIB_GSWE_PLANETS_H__

#include <glib.h>
#include <glib-object.h>

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
 * @GSWE_HOUSE_SISTEM_EQUAL: Equal house system
 */
typedef enum {
    GSWE_HOUSE_SYSTEM_NONE,
    GSWE_HOUSE_SYSTEM_PLACIDUS,
    GSWE_HOUSE_SYSTEM_KOCH,
    GSWE_HOUSE_SISTEM_EQUAL
} GsweHouseSystem;

/**
 * GsweMoonPhase:
 * @GSWE_MOON_PHASE_NEW: New Moon
 * @GSWE_MOON_PHASE_WAXING_CRESCENT: Waxing crescent Moon
 * @GSWE_MOON_PHASE_WAXING_HALF: First half
 * @GSWE_MOON_PHASE_WAXING_GIBBOUS: Waxing gibbous Moon
 * @GSWE_MOON_PHASE_FULL: Full Moon
 * @GSWE_MOON_PHASE_WANING_GIBBOUS: Waning gibbous Moon
 * @GSWE_MOON_PHASE_WANING_HALF: Second Half
 * @GSWE_MOON_PHASE_WANING_CRESCENT: Waning crescent Moon
 * @GSWE_MOON_PHASE_DARK: Dark Moon
 */
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

/**
 * GsweSignInfo:
 * @sign_id: the identifier for this sign
 * @name: the name of this sign
 * @element: the element of the sign
 * @quality: the quality of the sign
 */
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

/**
 * GsweAspectInfo:
 * @aspect: the identifier of this aspect
 * @name: the name of the aspect
 * @size: the size of the aspect, in degrees
 * @orb_modifier: the modifier of the orb (the maximum allowable difference from an exact orb)
 * @harmonic: shows whether this aspect is harmonic or not
 * @major: shows whether this aspect is major (Ptolemaic) or not
 */
typedef struct {
    GsweAspect aspect;
    gchar *name;
    guint size;
    guint orb_modifier;
    gboolean harmonic;
    gboolean major;
} GsweAspectInfo;

/**
 * GsweAntiscionInfo:
 * @axis_id: the identifier of this mirror's axis
 * @start_sign: represents the sign in whict the mirror axis starts
 * @name: the name of the mirror
 * @middle_axis: if TRUE, the axis runs through the middle of its starting sign
 */
typedef struct {
    GsweAntiscionAxis axis_id;
    GsweSignInfo *start_sign;
    gchar *name;
    gboolean middle_axis;
} GsweAntiscionInfo;

/**
 * GsweMoonPhaseData:
 * @phase: the current phase of the Moon
 * @illumination: the portion of the Moon that is currently illuminated
 */
typedef struct {
    GsweMoonPhase phase;
    gdouble illumination;
} GsweMoonPhaseData;

GType gswe_moon_phase_data_get_type(void);
#define GSWE_TYPE_MOON_PHASE_DATA (gswe_moon_phase_data_get_type())

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

GType gswe_planet_data_get_type(void);
#define GSWE_TYPE_PLANET_DATA (gswe_planet_data_get_type())

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
 * GsweAntiscionData:
 * @planet1: the first planet in the antiscion
 * @planet2: the second planet in the antiscion
 * @axis: the axis on which this antiscion is
 * @antiscion_info: the #GsweAntiscionInfo structure associated with this
 *                  antiscion
 * @difference: the difference in degrees between an exact antiscion and this
 *              given antiscion
 */
typedef struct {
    GswePlanetData *planet1;
    GswePlanetData *planet2;
    GsweAntiscionAxis axis;
    GsweAntiscionInfo *antiscion_info;
    gdouble difference;
} GsweAntiscionData;

#endif /* __SWE_GLIB_GSWE_PLANETS_H__ */

