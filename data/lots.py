# -*- coding: utf8

import re
import logging
from collections import OrderedDict


def get_planet_name(planet):
    if planet == 'ASC':
        return 'ASCENDANT'

    if planet == 'S. Node':
        return 'MOON_SOUTH_NODE'

    if planet.upper() in known_planets:
        return planet.upper()

    return None


def get_planet_def(planet):
    PLANET_NAME = 0
    CUSP = 1
    RULER = 2
    SIGN = 3
    SIGN_DEGREE = 4
    SIGN_MINUTE = 5
    HOUSE_RULER = 6
    ARABIC_LOT = 7
    PLANET_HOUSE_RULER = 8

    planet_def = [
        get_planet_name(planet),  # 0, PLANET_NAME
        0,                        # 1, CUSP
        None,                     # 2, RULER
        None,                     # 3, SIGN
        0,                        # 4, SIGN_DEGREE
        0,                        # 5, SIGN_MINUTE
        0,                        # 6, HOUSE_RULER
        None,                     # 7, ARABIC_LOT
        None,                     # 8, PLANET_HOUSE_RULER
    ]

    sign_match = re.match(r'^(\d{2})([A-Z]{2})(\d{2})$', planet)

    if planet_def[PLANET_NAME] is None:
        if planet.startswith('Ruler of ') and \
           get_planet_name(planet[9:]) is not None:
            planet_def[RULER] = get_planet_name(planet[9:])
        elif planet.startswith('Ruler '):
            m1 = re.match(r'Ruler (\d+)(st|nd|rd|th)', planet)
            m2 = re.match(r"Ruler (\w+)'s house", planet)

            if m1 is not None:
                planet_def[HOUSE_RULER] = int(m1.groups()[0])

            elif m2 is not None:
                planet_def[PLANET_HOUSE_RULER] = get_planet_name(
                    m2.groups()[0])

                if planet_def[PLANET_HOUSE_RULER] is None:
                    logging.error(
                        "Error: planet house ruler definition error: {}"
                        .format(planet))

                    return None
            else:
                logging.error(
                    "Error: House ruler definition problem: {}"
                    .format(planet))

                return None
        elif planet.startswith('Cusp '):
            m = re.match(r'^Cusp (\d+)(st|nd|rd|th)', planet)

            if m is None:
                logging.error("Cusp definition problem: {}"
                              .format(planet))

                return None

            planet_def[CUSP] = int(m.groups()[0])
        elif sign_match is not None:
            degree, sign, minute = sign_match.groups()

            planet_def[SIGN] = next(s for s in signs if s.startswith(sign))
            planet_def[SIGN_DEGREE] = int(degree)
            planet_def[SIGN_MINUTE] = int(minute)
        elif planet.startswith('PO '):
            p_lot = planet[3:]

            if not any(x['c_name'] for y, x in lots.items()
                       if p_lot.upper() == x['c_name']):
                logging.error("Error: Unknown lot: {}".format(planet))

                return None

            planet_def[ARABIC_LOT] = p_lot.upper()
        else:
            logging.error("Unknown planet definition: {}".format(planet))

            return None

    planet_def = map(lambda x: 'NONE' if x is None else x, planet_def)

    return """
            {{
                GSWE_PLANET_{name},
                {cusp},
                GSWE_PLANET_{ruler},
                GSWE_SIGN_{sign}, {sign_degree}, {sign_minute},
                {house_ruler},
                GSWE_ARABIC_LOT_{arabic_lot},
                GSWE_PLANET_{planet_house_ruler}
            }}""".format(
                name=planet_def[PLANET_NAME],
                cusp=planet_def[CUSP],
                ruler=planet_def[RULER],
                sign=planet_def[SIGN],
                sign_degree=planet_def[SIGN_DEGREE],
                sign_minute=planet_def[SIGN_MINUTE],
                house_ruler=planet_def[HOUSE_RULER],
                arabic_lot=planet_def[ARABIC_LOT],
                planet_house_ruler=planet_def[PLANET_HOUSE_RULER],
            )

with open('lots.txt', 'r') as f:
    content = map(lambda line: line.strip(), f.readlines())

lots = OrderedDict()
c_names = set()
known_planets = [
    'MC',
    'VERTEX',
    'MOON_NODE',
    'MOON_APOGEE',
    'SUN',
    'MOON',
    'MERCURY',
    'VENUS',
    'EARTH',
    'MARS',
    'JUPITER',
    'SATURN',
    'URANUS',
    'NEPTUNE',
    'PLUTO',
    'CHIRON',
    'CERES',
    'PALLAS',
    'JUNO',
    'VESTA',
    'PHOLUS',
    'NESSUS',
    'CHARIKLO',
    'SEDNA',
    'ERIS',
    'DEJANIRA',
    'CIRCE',
    'ORCUS',
    'ASBOLUS',
    'HYGIEA',
]
signs = [
    'ARIES',
    'TAURUS',
    'GEMINI',
    'CANCER',
    'LEO',
    'VIRGO',
    'LIBRA',
    'SCORPIO',
    'SAGITTARIUS',
    'CAPRICORN',
    'AQUARIUS',
    'PISCES',
]

while content:
    line = content.pop(0)

    m = re.match('^([^=]+) = (.*)$', line)

    if not m:
        print("Error in line (no lot name): {}".format(line))

        continue

    lot_name, line = m.groups()

    line = line.strip()
    am_pm_rule = False

    if re.search('AM.*::.*PM', line):
        am_pm_rule = True
        line = line.split(' :: ')[0]
        s = re.search(' \([AP]M\)$', line)
        if s is None:
            print("Error in AM/PM line: {}".format(line))

            continue

        line = line[:-5]

    m = re.match('^([^-+]+) ([+-]) ([^-+]+) ([+-]) ([^-+]+)$', line)

    if not m:
        print("Error in line (doesn't match): {}".format(line))
        continue

    m = m.groups()

    if m[1] != '+' and m[3] != '-':
        print("Error in line: {}".format(line))

        continue

    if lot_name in lots and not am_pm_rule:
        print("Lot {} already exists!".format(lot_name))

        continue

    lot_name_def = re.sub(r'[^A-Z0-9_]', '',
                          re.sub(r'[ ,]+', '_', lot_name.upper()))

    if lot_name_def in c_names:
        print("Lot {} already exists in enum!".format(lot_name_def))

    lots[lot_name] = {
        "c_name": lot_name_def,
        "planets": (m[0], m[2], m[4]),
        "am_pm": am_pm_rule,
    }

enum = '''typedef enum _GsweArabicLot {
    GSWE_ARABIC_LOT_NONE,\n'''

defs = '''typedef struct _GsweArabicLotPart {
    GswePlanet planet;
    guint8 cusp;
    GswePlanet ruler;
    GsweZodiac fixed_sign;
    guint8 fixed_degree;
    guint8 fixed_minute;
    guint8 house_ruler;
    GsweArabicLot arabic_lot;
    GswePlanet planet_house_ruler;
} GsweArabicLotPart;

typedef struct _GsweArabicLotRecord {
    gchar *name;
    gboolean am_pm_rule;

    GsweArabicLotPart parts[3];
} GsweArabicLotRecord;

static const GsweArabicLotRecord known_lots[] = {
'''

for idx, (lot_name, lot) in enumerate(lots.items()):
    if idx != 0:
        enum += ',\n'
        defs += '\n'

    enum += '    GSWE_ARABIC_LOT_' + lot['c_name']

    defs += '    // Record for enum value ' + lot['c_name'] + '''
    {
        "''' + lot_name + '''",
        ''' + ("TRUE" if lot['am_pm'] else "FALSE") + ''',
        {'''

    for pidx, planet in enumerate(lot['planets']):
        defs += get_planet_def(planet)

        if pidx != 2:
            defs += ','

    defs += '''\n        }
    },\n'''

defs += '''    {NULL}
};'''

enum += '\n} GsweArabicLot;'

print("""/* gswe-lots.h - Arabic lot definitions for SWE-GLib
 *
 * Copyright © 2013  Gergely Polonkai
 *
 * SWE-GLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * SWE-GLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __GSWE_LOTS_H__
#define __GSWE_LOTS_H__

#include "gswe-types.h"
""" + enum + """

""" + defs + """

#endif /* __GSWE_LOTS_H__ */""")
