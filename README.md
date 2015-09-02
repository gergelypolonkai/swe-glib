# SWE-GLib

SWE-GLib is a GLib style wrapper library around Astrodienst's
[Swiss Ephemeris library](http://www.astro.com/swisseph/).

The source tree contains Astrodienst's ephemeride files, as requested
by Alois Treindl of Astrodienst in a mail written to me on 24 July,
2013.

## GTK-Doc

The project utilizes [GTK-Doc](http://www.gtk.org/gtk-doc/), requiring
version 1.19 or later. Although the generated documentation is a bit
messy (not everything is documented, and there are some unresolved
variables, like [SERVER] on the generated index page.

Still, the documentation generates well, and at least gives a clue
about object usage.

## Bindings

SWE-GLib utilizes
[GObject Introspection](https://wiki.gnome.org/GObjectIntrospection),
which means it is available for many languages. Check out the
[examples](examples) directory for some sample code!

## Usage

Many functions return non-opaque C structs; their documentation can be
found inline, and in the generated GTK-Doc. Unless otherwise stated,
the returned values should never be freed.

### Creating the required objects

Then you need to create a `GsweTimestamp` object:

```c
GsweTimestamp *timestamp = gswe_timestamp_new_from_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1.0);
```

The `GsweTimetamp` object is used to convert dates between the Gregorian calendar dates and Julian Day values (not to be confused with Julian calendar dates).

Next, you have to create a `GsweMoment` object:

```c
GsweMoment *moment = gswe_moment_new_full(timestamp, 19.081599, 47.462485, 300.0, GSWE_HOUSE_PLACIDUS);
```

The `GsweMoment` object holds information of a given moment at a given place on earth. `gswe_moment_new_full()` requires a `GsweTimestamp` object, some geographical coordinates (in degrees) together with altitude above sea level (in meters), and a house system to use.

### Adding planets

After that you have to add some planets you want to do calculations on.

```c
gswe_moment_add_planet(moment, GSWE_PLANET_SUN);
```

Alternatively, you can add every planets known by SWE-GLib with

```c
gswe_moment_add_all_planets(moment);
```

### Getting planet positions and such

Then, you can get the planet data with

```c
GswePlanetData *sun_data = gswe_moment_get_planet(moment, GSWE_PLANET_SUN);
```

### Getting aspects and antiscia

SWE-GLib is also able to calculate aspects and antiscia. This functionality does not exist in the Swiss Ephemeris library, though. For this, of course, you have to add multiple planets (at least two) to your `GsweMoment`. After that, you can call `gswe_moment_get_planet_aspects()` and `gswe_moment_get_planet_antiscia()`.

```c
GList *sun_aspects = gswe_moment_get_planet_aspects(moment, GSWE_PLANET_SUN);
GList *sun_antiscia = gswe_moment_get_planet_antiscia(moment, GSWE_PLANET_SUN);
```

The returned GList objects hold zero or more `GsweAspectData` or
`GsweAntiscionData` objects, respectively.

### Getting the Moon phase

Last, but not least, SWE-GLib can calculate Moon's phase at the given
moment. For that, you have to call `gswe_moment_get_moon_phase()`:

```c
GsweMoonPhaseData *moon_phase = gswe_moment_get_moon_phase(moment);
```

### About altitude

The Swiss Ephemeris library requires the altitude value to be
specified for several calculations. It also notifies how important it
is:

> the altitude above sea must be in meters. Neglecting the altitude
> can result in an error of about 2 arc seconds with the moon and at
> an altitude 3000m.

2 arc seconds is about 0.000555 degrees of error, which is, well, kind
of small. Of course, if you need very precise horoscopes or need
planetary positions for a totally different thing, you should really
provide a (close to) exact value; otherwise, it is safe to pass any
value (well, which seems logical: the average level of all dry lands
is about 840 meters; the average level of the whole planet Earth
(including oceans and seas) is around 280 meters. Providing a value of
~400 should be OK most of the time).

## API stability

The project is currently transitioning to 2.0. master is a bit fragile
at the moment, 1.x versions are considered to be stable (although see
commit 8f52aba about a huge typo-bug).

## Limitations

### Topocentric calculations only

Although the original Swiss Ephemeris library supports it, SWE-GLib
can't do Heliocentric, nor Geocentric (as seen from the center of
Earth) calculations, only Topocentric (as seen from a given point on
Earth’s surface) calculations yet.

### Database size

The size of all data files provided by Astrodienst is around
40MB. Although it should not be a problem with today's home hardware,
it can be a hard requirement on embedded systems. For basic
calculations, keeping the following files under $(datadir)/swe-glib is
usually enough:

* `seas_18.se1`
* `semo_18.se1`
* `sepl_18.se1`

### Fixed stars are not known yet

Although Swiss Ephemeris has the functionality to calculate the
position of fixed stars, SWE-GLib doesn't provide such
functionality. This, however, is a planned feature for the close
future.

## Licencing

As the underlying Swiss Ephemeris is published under GPL (or a
commercial license I can not afford), SWE-GLib is also uses that. This
means that you can currently use SWE-GLib in software published under
the GNU GPL v3 (or, at your option, any later version).
