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

static GsweHouseData *
gswe_house_data_copy(GsweHouseData *house_data)
{
    GsweHouseData *ret = g_new0(GsweHouseData, 1);

    ret->house = house_data->house;
    ret->cusp_position = house_data->cusp_position;
    ret->sign = house_data->sign;

    return ret;
}

G_DEFINE_BOXED_TYPE(GsweHouseData, gswe_house_data, (GBoxedCopyFunc)gswe_house_data_copy, (GBoxedFreeFunc)g_free);

static GsweAspectData *
gswe_aspect_data_copy(GsweAspectData *aspect_data)
{
    GsweAspectData *ret = g_new0(GsweAspectData, 1);

    ret->planet1 = aspect_data->planet1;
    ret->planet2 = aspect_data->planet2;
    ret->distance = aspect_data->distance;
    ret->aspect = aspect_data->aspect;
    ret->aspect_info = aspect_data->aspect_info;
    ret->difference = aspect_data->difference;

    return ret;
}

G_DEFINE_BOXED_TYPE(GsweAspectData, gswe_aspect_data, (GBoxedCopyFunc)gswe_aspect_data_copy, (GBoxedFreeFunc)g_free);

static GsweAntiscionData *
gswe_antiscion_data_copy(GsweAntiscionData *antiscion_data)
{
    GsweAntiscionData *ret = g_new0(GsweAntiscionData, 1);

    ret->planet1 = antiscion_data->planet1;
    ret->planet2 = antiscion_data->planet2;
    ret->axis = antiscion_data->axis;
    ret->antiscion_info = antiscion_data->antiscion_info;
    ret->difference = antiscion_data->difference;

    return ret;
}

G_DEFINE_BOXED_TYPE(GsweAntiscionData, gswe_antiscion_data, (GBoxedCopyFunc)gswe_antiscion_data_copy, (GBoxedFreeFunc)g_free);
