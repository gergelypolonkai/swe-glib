#undef G_DISABLE_ASSERT

#include <glib.h>
#include <glib-object.h>
#include <swe-glib.h>

#include "test-asserts.h"

struct testdata_t {
    gint year;
    guint month;
    guint day;
    guint hour;
    guint minute;
    guint second;
    guint ms;
    gdouble tz;
    gdouble jdet;
    gdouble jdut;
    gdouble jdsr;
};

static struct testdata_t td[] = {
    { 1983, 3, 7, 11, 54, 45, 948, 1.0, 2445400.954699264, 3, 4 },
    { 2013, 9, 1, 13, 52, 18, 419, 2.0, 2456536.994646754, 3, 4 },
    { 0 }
};

static void
test_timestamp_gregorian(void)
{
    GsweTimestamp *timestamp;
    GError *err = NULL;
    gint year;
    guint month, day, hour, minute, second, ms;
    gdouble tz;

    /* Create timestamp from testdata */
    timestamp = gswe_timestamp_new_from_gregorian_full(
            td[0].year, td[0].month, td[0].day,
            td[0].hour, td[0].minute, td[0].second, td[0].ms,
            td[0].tz
        );
    g_assert_nonnull(timestamp);

    /* Check for Gregorian validity */

    /* Set year, get year */
    gswe_timestamp_set_gregorian_year(timestamp, td[1].year, &err);
    g_assert_null(err);

    year = gswe_timestamp_get_gregorian_year(timestamp, &err);
    g_assert_null(err);
    g_assert_cmpint(year, ==, td[1].year);

    /* Set month, get month */
    gswe_timestamp_set_gregorian_month(timestamp, td[1].month, &err);
    g_assert_null(err);

    month = gswe_timestamp_get_gregorian_month(timestamp, &err);
    g_assert_null(err);
    g_assert_cmpuint(month, ==, td[1].month);

    /* Set day, get day */
    gswe_timestamp_set_gregorian_day(timestamp, td[1].day, &err);
    g_assert_null(err);

    day = gswe_timestamp_get_gregorian_day(timestamp, &err);
    g_assert_null(err);
    g_assert_cmpuint(day, ==, td[1].day);

    /* Set hour, get hour */
    gswe_timestamp_set_gregorian_hour(timestamp, td[1].hour, &err);
    g_assert_null(err);

    hour = gswe_timestamp_get_gregorian_hour(timestamp, &err);
    g_assert_null(err);
    g_assert_cmpuint(hour, ==, td[1].hour);

    /* Set minute, get minute */
    gswe_timestamp_set_gregorian_minute(timestamp, td[1].minute, &err);
    g_assert_null(err);

    minute = gswe_timestamp_get_gregorian_minute(timestamp, &err);
    g_assert_null(err);
    g_assert_cmpuint(minute, ==, td[1].minute);

    /* Set second, get second */
    gswe_timestamp_set_gregorian_second(timestamp, td[1].second, &err);
    g_assert_null(err);

    second = gswe_timestamp_get_gregorian_second(timestamp, &err);
    g_assert_null(err);
    g_assert_cmpuint(second, ==, td[1].second);

    /* Set ms, get ms */
    gswe_timestamp_set_gregorian_microsecond(timestamp, td[1].ms, &err);
    g_assert_null(err);

    ms = gswe_timestamp_get_gregorian_microsecond(timestamp, &err);
    g_assert_null(err);
    g_assert_cmpuint(ms, ==, td[1].ms);

    /* Set tz, get tz */
    gswe_timestamp_set_gregorian_timezone(timestamp, td[1].tz, &err);
    g_assert_null(err);

    tz = gswe_timestamp_get_gregorian_timezone(timestamp);
    g_assert_cmpfloat(tz, ==, td[1].tz);

    /* Set full, check all */
    gswe_timestamp_set_gregorian_full(
            timestamp,
            td[0].year, td[0].month, td[0].day,
            td[0].hour, td[0].minute, td[0].second, td[0].ms,
            td[0].tz,
            &err
        );
    g_assert_null(err);
    g_object_get(
            timestamp,
            "gregorian-year",            &year,
            "gregorian-month",           &month,
            "gregorian-day",             &day,
            "gregorian-hour",            &hour,
            "gregorian-minute",          &minute,
            "gregorian-second",          &second,
            "gregorian-microsecond",     &ms,
            "gregorian-timezone-offset", &tz,
            NULL
        );
    g_assert_cmpint(year,    ==, td[0].year);
    g_assert_cmpuint(month,  ==, td[0].month);
    g_assert_cmpuint(day,    ==, td[0].day);
    g_assert_cmpuint(hour,   ==, td[0].hour);
    g_assert_cmpuint(minute, ==, td[0].minute);
    g_assert_cmpuint(second, ==, td[0].second);
    g_assert_cmpuint(ms,     ==, td[0].ms);
    g_assert_cmpfloat(tz,    ==, td[0].tz);

    g_clear_object(&timestamp);
}

static void
test_timestamp_timezone(void)
{
    GsweTimestamp *timestamp;
    gdouble tz, val_old, val_new;
    guint hour, minute, second, ms;
    GError *err = NULL;

    /* Create timestamp */
    timestamp = gswe_timestamp_new_from_gregorian_full(
            td[0].year, td[0].month, td[0].day,
            td[0].hour, td[0].minute, td[0].second, td[0].ms,
            td[0].tz
        );
    g_assert_nonnull(timestamp);

    /* Change timezone */
    if (td[0].tz >= 23.0) {
        tz = td[0].tz - 1;
    } else {
        tz = td[0].tz + 1;
    }

    /* Check hour, minute, second and microsecond */
    val_old = (td[0].hour * 3600)
        + (td[0].minute * 60)
        + td[0].second
        + (td[0].ms / 1000.0);

    gswe_timestamp_set_gregorian_timezone(timestamp, tz, &err);
    g_assert_null(err);

    g_object_get(
            timestamp,
            "gregorian-hour",        &hour,
            "gregorian-minute",      &minute,
            "gregorian-second",      &second,
            "gregorian-microsecond", &ms,
            NULL
        );
    val_new = (hour * 3600)
        + (minute * 60)
        + second
        + (ms / 1000.0);

    g_assert_cmpfloat(val_new, !=, val_old);

    g_clear_object(&timestamp);
}

static void
test_timestamp_jdet(void)
{
    GsweTimestamp *timestamp;
    gdouble jdet;
    GError *err = NULL;

    /* Create timestamp */
    timestamp = gswe_timestamp_new_from_julian_day(td[0].jdet);
    g_assert_nonnull(timestamp);

    /* Check value */
    jdet = gswe_timestamp_get_julian_day_et(timestamp, &err);
    g_assert_null(err);
    gswe_assert_fuzzy_equals(jdet, td[0].jdet, 0.000001);

    /* Set new value */
    gswe_timestamp_set_julian_day_et(timestamp, td[1].jdet, &err);
    g_assert_null(err);

    /* Check value */
    jdet = gswe_timestamp_get_julian_day_et(timestamp, &err);
    g_assert_null(err);
    gswe_assert_fuzzy_equals(jdet, td[1].jdet, 0.000001);

    g_clear_object(&timestamp);
}

static void
test_timestamp_jdut(void)
{}

static void
test_timestamp_instant(void)
{
    GsweTimestamp *timestamp;
    gboolean instrecalc, greg_valid, jul_valid;
    GError *err = NULL;

    timestamp = gswe_timestamp_new_from_now_local();
    g_assert_nonnull(timestamp);

    g_object_get(
        timestamp,
        "instant-recalc", &instrecalc,
        "gregorian-valid", &greg_valid,
        "julian-day-valid", &jul_valid,
        NULL);
    g_assert_false(instrecalc);
    g_assert_true(greg_valid);
    g_assert_false(jul_valid);

    g_object_set(timestamp, "instant-recalc", TRUE, NULL);
    g_object_get(
        timestamp,
        "instant-recalc", &instrecalc,
        "gregorian-valid", &greg_valid,
        "julian-day-valid", &jul_valid,
        NULL);
    g_assert_true(instrecalc);
    g_assert_true(greg_valid);
    g_assert_true(jul_valid);

    g_object_set(timestamp, "instant-recalc", FALSE, NULL);
    gswe_timestamp_set_now_local(timestamp, &err);
    g_assert_null(err);
    g_object_get(
        timestamp,
        "instant-recalc", &instrecalc,
        "gregorian-valid", &greg_valid,
        "julian-day-valid", &jul_valid,
        NULL);
    g_assert_false(instrecalc);
    g_assert_true(greg_valid);
    g_assert_false(jul_valid);
}

static void
test_timestamp_conv_gregjd(void)
{
    GsweTimestamp *timestamp;
    gdouble jdet;
    GError *err = NULL;

    /* Create timestamp from testdata */
    timestamp = gswe_timestamp_new_from_gregorian_full(
            td[1].year, td[1].month, td[1].day,
            td[1].hour, td[1].minute, td[1].second, td[1].ms,
            td[1].tz
        );
    g_assert_nonnull(timestamp);

    jdet = gswe_timestamp_get_julian_day_ut(timestamp, &err);
    g_assert_null(err);

    /* Allow 5ms of fuzzyness here */
    gswe_assert_fuzzy_equals(
            jdet,
            td[1].jdet,
            0.0001
        );

    g_clear_object(&timestamp);
}

static void
test_timestamp_conv_jdgreg(void)
{}

static void
test_timestamp_sidereal(void)
{}

static void
test_timestamp_now(void)
{}

int
main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);

    g_test_add_func("/gswe/timestamp/gregorian", test_timestamp_gregorian);
    g_test_add_func("/gswe/timestamp/timezone", test_timestamp_timezone);
    g_test_add_func("/gswe/timestamp/jdet", test_timestamp_jdet);
    g_test_add_func("/gswe/timestamp/jdut", test_timestamp_jdut);
    g_test_add_func("/gswe/timestamp/instant", test_timestamp_instant);
    g_test_add_func("/gswe/timestamp/conv/greg_jd", test_timestamp_conv_gregjd);
    g_test_add_func("/gswe/timestamp/conv/jd_greg", test_timestamp_conv_jdgreg);
    g_test_add_func("/gswe/timestamp/sidereal", test_timestamp_sidereal);
    g_test_add_func("/gswe/timestamp/now", test_timestamp_now);

    return g_test_run();
}
