require "gir_ffi"

GirFFI.setup :SweGlib

SweGlib.init

timestamp = SweGlib::Timestamp.new
timestamp.set_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1)

moment = SweGlib::Moment.new

moment.set_timestamp(timestamp)
moment.set_coordinates(19.03991, 47.49801, 280)
moment.set_house_system :placidus
moment.add_all_planets

all_planets = moment.get_all_planets()

all_planets.each do |planet|
  # TODO Why do I get numbers here, instead of GswePlanets?
  print planet, "\n"
end
