var Swe = imports.gi.SweGlib;

Swe.init();

var timestamp = new Swe.Timestamp();
timestamp.set_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1);

moment = new Swe.Moment();
moment.add_all_planets();
moment.set_timestamp(timestamp);
moment.set_coordinates(19.03990999, 47.49801000, 280);
moment.set_house_system(Swe.HouseSystem.PLACIDUS);

planet = moment.get_planet(Swe.Planet.SUN);
log(planet.position);
