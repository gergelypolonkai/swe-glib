package SweGlib;

use strict;
use POSIX;
use Glib::Object::Introspection;

use Data::Dumper;

Glib::Object::Introspection->setup(basename => 'SweGlib', version => '2.0', package => 'SweGlib');

package main;

SweGlib::init();

my $timestamp = SweGlib::Timestamp->new();
$timestamp->set_gregorian_full(1983, 3, 7, 11, 54, 45, 0, 1);

my $moment = SweGlib::Moment->new();
$moment->set_timestamp($timestamp);
$moment->set_coordinates(19.0390999, 47.49801000, 280);
$moment->set_house_system("placidus");
$moment->add_all_planets();

my $all_planets = $moment->get_all_planets();
foreach my $planet (@{$all_planets}) {
    my $position = $planet->get_position();
    my $sign_position = POSIX::fmod($position, 30);
    my $degree = POSIX::floor($sign_position);
    my $minute = POSIX::floor(($sign_position - $degree) * 60);
    my $second = POSIX::floor((($sign_position - $degree) * 60 - $minute) * 60);

    printf("%s: %f (%d°%d′%d″ %s)\n", $planet->get_planet_info()->get_name(), $position, $degree, $minute, $second, $planet->get_sign_info()->get_name());
}

my $all_aspects = $moment->get_all_aspects();
foreach my $aspect (@{$all_aspects}) {
    if ($aspect->get_aspect() ne "none") {
        my $planet1 = $aspect->get_planet1();
        my $planet2 = $aspect->get_planet2();

        printf("%s in %s with %s (±%.2f%%)\n", $planet1->get_planet_info()->get_name(), $aspect->get_aspect_info->get_name(), $planet2->get_planet_info()->get_name(), $aspect->get_difference());
    }
}

my $all_antiscia = $moment->get_all_antiscia();
foreach my $antiscion (@{$all_antiscia}) {
    if ($antiscion->get_axis() ne "none") {
        my $planet1 = $antiscion->get_planet1();
        my $planet2 = $antiscion->get_planet2();

        printf("%s is antiscion of %s on axis %s (±%.2f%%)\n", $planet1->get_planet_info()->get_name(), $planet2->get_planet_info()->get_name(), $antiscion->get_antiscion_axis_info()->get_name(), $antiscion->get_difference());
    }
}

