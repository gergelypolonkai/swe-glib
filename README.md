# SWE-GLib

SWE-GLib is a GLib style wrapper library around the [Swiss Ephemeris library](http://www.astro.com/swisseph/), created by Astrodienst.

The source tree contains Astrodienst's (the writers/publishers of the Swiss Ephemeris library) ephemeride files, as requested by Alois Treindl of Astrodienst in a mail written to me on 24 July, 2013.

## Usage

For exact calculations, you need to create a GsweTimestamp object:

```c
GsweTimestamp *timestamp = gswe_timestamp_new_from_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1.0);
```

The GsweTimetamp object is used to convert dates between the Gregorian calendar dates and Julian Day values (not to be confused with Julian calendar dates!).

Next, you have to create a GsweMoment object:

```c
GsweMoment *moment = gswe_moment_new_full(timestamp, 19.081599, 47.462485, 300.0, GSWE_HOUSE_PLACIDUS);
```

The GsweMoment object holds information of a given moment at a given place on earth. `gswe_moment_new_full()` requires a `GsweTimestamp` object, some geographical coordinates together with altitude above sea level (coordinates must be given in degrees, while altitude in meters!), and a house system to use.

### About altitude

The Swiss Ephemeris library requires the altitude value to be specified for several calculations. It also notifies how important it is:

> the altitude above sea must be in meters. Neglecting the altitude can result in an error of about 2 arc seconds with the moon and at an altitude 3000m.

2 arc seconds is about 0.000555 degrees of error, which is, well, kind of small. Of course, if you need very precise horoscopes, precise horoscopes; otherwise, it is safe to pass any value (well, that seems logical. The average level of all dry lands is about 840 meters; the average level of the whole planet Earth (including oceans and seas) is around 280 meters).

## API stability

The project is currently marked as 1.0. However, without further notice, the API should not be seen as stable.

This means that some function prototypes may be modified in the near future. Mostly error handling routines are missing, so some functions will get a `GError **` parameter.

Otherwise, the API is final, in term of future compatibility. New functions may be added later, though.
