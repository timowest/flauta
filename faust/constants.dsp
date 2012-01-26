/*
 *  Copyright (C) 2011 Timo Westkämper, Carlos Barría, Daniel Tirado and Patricio de la Cuadra
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

// constants

AIR_DENSITY = 1.2;
HALF_DENSITY = AIR_DENSITY / 2;
MAX_AMPLITUDE = 1.2e-4 * 0.5 * AIR_DENSITY;
M_PI = 3.141592654;
ONE_OVER_RHO_C = 1.0 / (AIR_DENSITY * SOUND_SPEED);
RAD_ORDER = 3.0;
SOUND_SPEED = 343.54;
TWO_div_M_PI = 2.0 / M_PI;
TWO_SOUND_SPEED = 687.08;
VT_ORDER = 4.0;
VORTEX_CTE = -0.5 * AIR_DENSITY * (1 / 0.36);

ONE_OVER_128 = 1/128;

//MAX_DELAY_LENGTH = 4096;
MAX_DELAY_LENGTH = 10000;
