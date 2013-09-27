package SweGlib;

use Glib::Object::Introspection;

Glib::Object::Introspection->setup(basename => 'SweGlib', version => '1.0', package => 'SweGlib');

package main;

SweGlib::init();

$timestamp = SweGlib::Timestamp->new();
$timestamp->set_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1);

$moment = SweGlib::Moment->new();
$moment->set_timestamp($timestamp);
$moment->set_coordinates(19.0390999, 47.49801000, 280);
$moment->set_house_system("placidus");
$moment->add_all_planets();

$planet = $moment->get_planet("sun");
print($planet->position, "\n");
