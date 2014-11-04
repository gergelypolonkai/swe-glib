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

local all_planets = moment:get_all_planets()
for _, planet in ipairs(all_planets) do
   local position = planet:get_position()
   local sign_position = math.fmod(position, 30)
   local degree = math.floor(sign_position)
   local minute = math.floor((sign_position - degree) * 60)
   local second = math.floor(((sign_position - degree) * 60 - minute) * 60)
   io.write(string.format("%s: %f (%d°%d′%d″ %s)\n", planet:get_planet_info():get_name(), position, degree, minute, second, planet:get_sign_info():get_name()))
end

local all_aspects = moment:get_all_aspects()
for _, aspect in ipairs(all_aspects) do
   if aspect:get_aspect() ~= "NONE" then
      local planet1 = aspect:get_planet1()
      local planet2 = aspect:get_planet2()

      io.write(string.format("%s in %s with %s (±%.2f%%)\n", planet1:get_planet_info():get_name(), aspect:get_aspect_info():get_name(), planet2:get_planet_info():get_name(), aspect:get_difference()))
   end
end

local all_antiscia = moment:get_all_antiscia()
for _, antiscion in ipairs(all_antiscia) do
   if antiscion:get_axis() ~= "NONE" then
      local planet1 = antiscion:get_planet1()
      local planet2 = antiscion:get_planet2()

      io.write(string.format("%s is antiscion of %s on axis %s (±%.2f%%)\n", planet1:get_planet_info():get_name(), planet2:get_planet_info():get_name(), antiscion:get_antiscion_axis_info():get_name(), antiscion:get_difference()))
   end
end
