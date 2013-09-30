local lgi = require 'lgi'
local SweGlib = lgi.require('SweGlib', '2.0')

SweGlib.init()

local timestamp = SweGlib.Timestamp.new()
timestamp:set_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1)

local moment = SweGlib.Moment.new()
moment:set_timestamp(timestamp)
moment:set_timestamp(timestamp)
moment:set_coordinates(19.03990999, 47.49801000, 280)
moment:set_house_system(SweGlib.HouseSystem.PLACIDUS)
moment:add_all_planets()

local planet = moment:get_planet(SweGlib.Planet.SUN)
io.write(planet:get_position(), "\n")
