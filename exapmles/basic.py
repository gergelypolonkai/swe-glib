from gi.repository import SweGlib

SweGlib.init()

timestamp = SweGlib.Timestamp()
timestamp.set_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1)

moment = SweGlib.Moment()
moment.set_timestamp(timestamp)
moment.set_coordinates(19.03990999, 47.49801000, 280)
moment.set_house_system(SweGlib.HouseSystem.PLACIDUS)
moment.add_all_planets()

planet = moment.get_planet(SweGlib.Planet.SUN)
print planet.position
