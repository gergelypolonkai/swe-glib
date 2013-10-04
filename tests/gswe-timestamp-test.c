#undef G_DISABLE_ASSERT

#include <glib.h>
#include <glib-object.h>
#include <swe-glib.h>

static void
test_timestamp_jd(void)
{
    GsweTimestamp *timestamp;
    gdouble jd;

    timestamp = gswe_timestamp_new_from_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1);
    g_assert(timestamp);

    jd = gswe_timestamp_get_julian_day(timestamp, NULL);
    g_assert(jd == 2445400.9553030556999146938323974609375);

    g_object_unref(timestamp);

    timestamp = gswe_timestamp_new_from_julian_day(jd);
    g_assert(timestamp);
    g_assert(gswe_timestamp_get_gregorian_year(timestamp, NULL) == 1983);
    g_assert(gswe_timestamp_get_gregorian_month(timestamp, NULL) == 3);
    g_assert(gswe_timestamp_get_gregorian_day(timestamp, NULL) == 7);
    g_assert(gswe_timestamp_get_gregorian_hour(timestamp, NULL) == 11);
    g_assert(gswe_timestamp_get_gregorian_minute(timestamp, NULL) == 54);
    g_assert(gswe_timestamp_get_gregorian_second(timestamp, NULL) == 45);
    g_assert(gswe_timestamp_get_gregorian_microsecond(timestamp, NULL) == 0);
}

int
main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);

    g_test_add_func("/gswe-timestamp/jd", test_timestamp_jd);

    return g_test_run();
}
