#undef G_DISABLE_ASSERT

#include <glib.h>
#include <glib-object.h>
#include <swe-glib.h>

#include "test-asserts.h"

static void
test_timestamp_jd(void)
{
    GsweTimestamp *timestamp;
    gdouble jd,
            seconds;

    timestamp = gswe_timestamp_new_from_gregorian_full(
            1983, 3, 7,
            11, 54, 45, 0,
            1.0
        );
    g_assert(timestamp);

    jd = gswe_timestamp_get_julian_day_et(timestamp, NULL);

    g_object_unref(timestamp);

    timestamp = gswe_timestamp_new_from_julian_day(jd);
    g_assert(timestamp);
    gswe_timestamp_set_gregorian_timezone(timestamp, 1.0, NULL);
    g_assert_cmpfloat(
            gswe_timestamp_get_gregorian_timezone(timestamp),
            ==,
            1.0
        );
    g_assert_cmpint(
            gswe_timestamp_get_gregorian_year(timestamp, NULL),
            ==,
            1983
        );
    g_assert_cmpuint(
            gswe_timestamp_get_gregorian_month(timestamp, NULL),
            ==,
            3
        );
    g_assert_cmpuint(gswe_timestamp_get_gregorian_day(timestamp, NULL), ==, 7);
    g_assert_cmpuint(
            gswe_timestamp_get_gregorian_hour(timestamp, NULL),
            ==,
            11
        );
    g_assert_cmpuint(
            gswe_timestamp_get_gregorian_minute(timestamp, NULL),
            ==,
            54
        );

    seconds =
        gswe_timestamp_get_gregorian_second(timestamp, NULL)
        + gswe_timestamp_get_gregorian_microsecond(timestamp, NULL) / 1000.0;

    /* Due to floating point errors, we allow 5 microseconds fuzzyness here */
    gswe_assert_fuzzy_equals(
            seconds,
            45.0,
            0.005
        );
}

int
main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);

    g_test_add_func("/gswe-timestamp/jd", test_timestamp_jd);

    return g_test_run();
}

