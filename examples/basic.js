const GLib = imports.gi.GLib;
const Swe = imports.gi.SweGlib;
const Format = imports.format;

String.prototype.format = Format.format;

Swe.init();

var timestamp = new Swe.Timestamp();
timestamp.set_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1);

var moment = new Swe.Moment();
moment.add_all_planets();
moment.set_timestamp(timestamp);
moment.set_coordinates(19.03991, 47.49801, 280);
moment.set_house_system(Swe.HouseSystem.PLACIDUS);

var all_planets = moment.get_all_planets()
for (var i = 0; i < all_planets.length; i++) {
    var planet = all_planets[i];
    var position = planet.get_position();
    var sign_position = position % 30;
    var degree = Math.floor(sign_position);
    var minute = Math.floor((sign_position - degree) * 60);
    var second = Math.floor(((sign_position - degree) * 60 - minute) * 60)

    print("%s: %.6f (%d°%d′%d″ %s)".format(planet.get_planet_info().get_name(), position, degree, minute, second, planet.get_sign_info().get_name()));
}

var all_aspects = moment.get_all_aspects();
for (var i = 0; i < all_aspects.length; i++) {
    var aspect = all_aspects[i];

    if (aspect.get_aspect() != Swe.Aspect.NONE) {
        var planet1 = aspect.get_planet1();
        var planet2 = aspect.get_planet2();

        print("%s in %s with %s (±%.2f%%)".format(planet1.get_planet_info().get_name(), aspect.get_aspect_info().get_name(), planet2.get_planet_info().get_name(), aspect.get_difference()));
    }
}

var all_antiscia = moment.get_all_antiscia();
for (var i = 0; i < all_antiscia.length; i++) {
    var antiscion = all_antiscia[i];

    if (antiscion.get_axis() != Swe.AntiscionAxis.NONE) {
        var planet1 = antiscion.get_planet1();
        var planet2 = antiscion.get_planet2();

        print("%s is antiscion of %s on axis %s (±%.2f%%)".format(planet1.get_planet_info().get_name(), planet2.get_planet_info().get_name(), antiscion.get_antiscion_axis_info().get_name(), antiscion.get_difference().toFixed(2)));
    }
}
