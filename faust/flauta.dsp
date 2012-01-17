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

// Flauta

// common libs
import("filter.lib");
import("music.lib");

// flauta libs
import("resonator.dsp");
import("excitation.dsp");
import("constants.dsp");
import("params.dsp");
//import("utils.dsp");

// flauta
flauta = ((((exc:resonator)~_):(!,_,_))~_):(!,_) ;
exc = excitation : (_+_/2);


process = flauta;
  



