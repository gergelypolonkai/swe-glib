#include "gswe-types.h"

static GsweMoonPhaseData *
gswe_moon_phase_data_copy(GsweMoonPhaseData *moon_phase_data)
{
    GsweMoonPhaseData *ret = g_new0(GsweMoonPhaseData, 1);

    ret->phase = moon_phase_data->phase;
    ret->illumination = moon_phase_data->illumination;

    return ret;
}

G_DEFINE_BOXED_TYPE(GsweMoonPhaseData, gswe_moon_phase_data, (GBoxedCopyFunc)gswe_moon_phase_data_copy, (GBoxedFreeFunc)g_free);

static GswePlanetData *
gswe_planet_data_copy(GswePlanetData *planet_data)
{
    GswePlanetData *ret = g_new0(GswePlanetData, 1);

    ret->planet_id = planet_data->planet_id;
    ret->planet_info = planet_data->planet_info;
    ret->position = planet_data->position;
    ret->retrograde = planet_data->retrograde;
    ret->house = planet_data->house;
    ret->sign = planet_data->sign;
    ret->revision = planet_data->revision;

    return ret;
}

G_DEFINE_BOXED_TYPE(GswePlanetData, gswe_planet_data, (GBoxedCopyFunc)gswe_planet_data_copy, (GBoxedFreeFunc)g_free);

GsweCoordinates *
gswe_coordinates_copy(GsweCoordinates *coordinates)
{
    GsweCoordinates *ret = g_new0(GsweCoordinates, 1);

    ret->longitude = coordinates->longitude;
    ret->latitude = coordinates->latitude;
    ret->altitude = coordinates->altitude;

    return ret;
}

G_DEFINE_BOXED_TYPE(GsweCoordinates, gswe_coordinates, (GBoxedCopyFunc)gswe_coordinates_copy, (GBoxedFreeFunc)g_free);

