/* gswe-lots.h - Arabic lot definitions for SWE-GLib
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
#include "gswe-enumtypes.h"
#include "gswe-lots.h"

typedef struct _GsweArabicLotPart {
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
    // Record for enum value FORTUNE
    {
        "Fortune",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ABILITY
    {
        "Ability",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_ASCENDANT,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ABUNDANCE
    {
        "Abundance",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ACCIDENT
    {
        "Accident",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ACCOMPLISHMENT
    {
        "Accomplishment",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ACTIONREASONING
    {
        "Action/Reasoning",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ADDICTION
    {
        "Addiction",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON_SOUTH_NODE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ADMINISTRATORS
    {
        "Administrators",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value AGRICULTURE
    {
        "Agriculture",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ALLEGIANCE
    {
        "Allegiance",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ANCESTORSRELATIONS
    {
        "Ancestors/Relations",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ANCESTRAL_HERITAGE
    {
        "Ancestral Heritage",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                8,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ARMIES
    {
        "Armies",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ART
    {
        "Art",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ASSASSINATION_1
    {
        "Assassination (1)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                12,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ASSASSINATION_2
    {
        "Assassination (2)",
        FALSE,
        {
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ASSURANCE
    {
        "Assurance",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ASTROLOGY
    {
        "Astrology",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value BAD_LUCK
    {
        "Bad Luck",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_FORTUNE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_SPIRIT,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value BANKRUPTCY_1
    {
        "Bankruptcy (1)",
        FALSE,
        {
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value BANKRUPTCY_2
    {
        "Bankruptcy (2)",
        FALSE,
        {
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value BEAUTY
    {
        "Beauty",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value BENIFIC_CHANGE
    {
        "Benific Change",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_PLUTO,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value BENEVOLENCE
    {
        "Benevolence",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_PLUTO,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value BUSINESS_PARTNERSHIPS
    {
        "Business Partnerships",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                7,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                10,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value CANCER
    {
        "Cancer",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value CATASTROPHE_1
    {
        "Catastrophe (1)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value CATASTROPHE_2
    {
        "Catastrophe (2)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value CAUTION
    {
        "Caution",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value CHILDREN
    {
        "Children",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value COMMERCE_1
    {
        "Commerce (1)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value COMMERCE_2
    {
        "Commerce (2)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value CONTROVERSY
    {
        "Controversy",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value CORRUPTNESS
    {
        "Corruptness",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value CURIOSITY
    {
        "Curiosity",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DAMAGE
    {
        "Damage",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DANGER_VIOLENCE_DEBT
    {
        "Danger, Violence, Debt",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DAUGHTERS
    {
        "Daughters",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DEATH
    {
        "Death",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                8,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DEATH_PARENTS
    {
        "Death (Parents)",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DEBT
    {
        "Debt",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DESIRE_SEXUAL_ATTRACTION
    {
        "Desire, Sexual Attraction",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                5,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                5,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DESTINY
    {
        "Destiny",
        TRUE,
        {
            {
                GSWE_PLANET_MC,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DESTRUCTION
    {
        "Destruction",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DISEASE
    {
        "Disease",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DIVORCE_1
    {
        "Divorce (1)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                7,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value DIVORCE_2
    {
        "Divorce (2)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                7,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ECCENTRICITY
    {
        "Eccentricity",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value ENERGY_SEX_DRIVE
    {
        "Energy, Sex Drive",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_PLUTO,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value EXPECTED_BIRTH_1
    {
        "Expected Birth (1)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_MOON
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value EXPECTED_BIRTH_2
    {
        "Expected Birth (2)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value FAME
    {
        "Fame",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value FAMOUS_FRIENDS
    {
        "Famous Friends",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_FORTUNE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value FASCINATION
    {
        "Fascination",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value FATE_KARMA
    {
        "Fate (Karma)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value FATHER
    {
        "Father",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value FRAUD
    {
        "Fraud",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value FRIENDS_1
    {
        "Friends (1)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value FRIENDS_2
    {
        "Friends (2)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value FRIENDS_3
    {
        "Friends (3)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value GENIUS
    {
        "Genius",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value GRANDPARENTS_1
    {
        "Grandparents (1)",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                2,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value GRANDPARENTS_2
    {
        "Grandparents (2)",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                2,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value GUIDANCE
    {
        "Guidance",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value HAPPINESS
    {
        "Happiness",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value HOMOSEXUALITY
    {
        "Homosexuality",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value HORSEMANSHIP
    {
        "Horsemanship",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value IDENTITY
    {
        "Identity",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value IMPRISONMENT
    {
        "Imprisonment",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value INCREASE
    {
        "Increase",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value INHERITANCE_1
    {
        "Inheritance (1)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value INHERITANCE_2
    {
        "Inheritance (2)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value JOURNEYS_AIR
    {
        "Journeys (Air)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                9,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value JOURNEYS_LAND
    {
        "Journeys (Land)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                9,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                9,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value JOURNEYS_WATER
    {
        "Journeys (Water)",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_CANCER, 15, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value KINGS_RULERS
    {
        "Kings, Rulers",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value KNOWLEDGE
    {
        "Knowledge",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value LIFE_REINCARNATION
    {
        "Life, Reincarnation",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value LOVE
    {
        "Love",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value LOVERS
    {
        "Lovers",
        FALSE,
        {
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                5,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value LUCK
    {
        "Luck",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value MARRIAGE
    {
        "Marriage",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                7,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value MARRIAGE_OF_WOMAN_1
    {
        "Marriage of Woman (1)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value MARRIAGE_OF_WOMAN_2
    {
        "Marriage of Woman (2)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value MARRIAGE_OF_MAN_1
    {
        "Marriage of Man (1)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value MARRIAGE_OF_MAN_2
    {
        "Marriage of Man (2)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value MOTHER
    {
        "Mother",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value PARTNERS
    {
        "Partners",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                7,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value PERIL
    {
        "Peril",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                8,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value POSSESSIONS
    {
        "Possessions",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                2,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                2,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value REAL_ESTATE_LAND
    {
        "Real Estate (Land)",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value REAL_ESTATE_INVESTMENT
    {
        "Real Estate (Investment)",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MERCURY,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SECRET_ENEMIES
    {
        "Secret Enemies",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SHORT_JOURNEYS
    {
        "Short Journeys",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                3,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                3,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SIBLINGS
    {
        "Siblings",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SICKNESS
    {
        "Sickness",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SONINLAWS
    {
        "Son-in-Laws",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SONS
    {
        "Sons",
        FALSE,
        {
            {
                GSWE_PLANET_NONE,
                4,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SPIRIT
    {
        "Spirit",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SUCCESS
    {
        "Success",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_FORTUNE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SUCCESS_INVESTMENT
    {
        "Success (Investment)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SUICIDE_1
    {
        "Suicide (1)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                8,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SUICIDE_2
    {
        "Suicide (2)",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value SURGERY
    {
        "Surgery",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MARS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value TRAGEDY
    {
        "Tragedy",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SATURN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_SUN,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value UNUSUAL_EVENTS
    {
        "Unusual Events",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_URANUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_MOON,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value VICTORY
    {
        "Victory",
        TRUE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_JUPITER,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_SPIRIT,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value WEDDINGS_LEGAL_CONTRACTS
    {
        "Weddings, Legal Contracts",
        FALSE,
        {
            {
                GSWE_PLANET_NONE,
                9,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                3,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_VENUS,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },

    // Record for enum value WIDOWHOOD
    {
        "Widowhood",
        FALSE,
        {
            {
                GSWE_PLANET_ASCENDANT,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NONE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_LIBRA, 8, 50,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            },
            {
                GSWE_PLANET_NEPTUNE,
                0,
                GSWE_PLANET_NONE,
                GSWE_SIGN_NONE, 0, 0,
                0,
                GSWE_ARABIC_LOT_NONE,
                GSWE_PLANET_NONE
            }
        }
    },
    {NULL}
};

#endif /* __GSWE_LOTS_H__ */
