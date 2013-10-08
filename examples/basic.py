from gi.repository import SweGlib

SweGlib.init()

timestamp = SweGlib.Timestamp()
timestamp.set_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1)

moment = SweGlib.Moment()
moment.set_timestamp(timestamp)
moment.set_coordinates(19.03990999, 47.49801000, 280)
moment.set_house_system(SweGlib.HouseSystem.PLACIDUS)
moment.add_all_planets()

all_planets = moment.get_all_planets()
for planet in all_planets:
    print "%s: %f" % (planet.get_planet_info().get_name(), planet.get_position())

all_aspects = moment.get_all_aspects()
for aspect in all_aspects:
    if aspect.get_aspect() != SweGlib.Aspect.NONE:
        planet1 = aspect.get_planet1()
        planet2 = aspect.get_planet2()
        print "%s in %s with %s" % (planet1.get_planet_info().get_name(), aspect.get_aspect_info().get_name(), planet2.get_planet_info().get_name())

all_antiscia = moment.get_all_antiscia()
for antiscion in all_antiscia:
    if antiscion.get_axis() != SweGlib.AntiscionAxis.NONE:
        planet1 = antiscion.get_planet1()
        planet2 = antiscion.get_planet2()
        print "%s is antiscion of %s on axis %s" % (planet1.get_planet_info().get_name(), planet2.get_planet_info().get_name(), antiscion.get_antiscion_axis_info().get_name())
