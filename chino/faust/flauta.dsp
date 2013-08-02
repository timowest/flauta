/*
 *  Copyright (C) 2011 Timo WestkÃÂ¤mper, Carlos BarrÃÂ­a, Daniel Tirado and Patricio de la Cuadra
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
import("constants.dsp");
import("params.dsp");
import("excitation.dsp");
import("resonator.dsp");
//import("utils.dsp");

// flauta
flauta = (excitation : resonator) ~ (_,_) : (!,!,_) : (dac_scale * _) <: (_,_) ;

process(pressure,turbulence_gain,vortex_ampli1,vortex_ampli2,channel_length,jet_height,jet_shape,labium_position,flue_labium_distance,delta_d,vibrato_gain,vibrato_freq,env_attack,env_decay,env_sustain,env_release,length1,length2,radius1,radius2,lossescoef) = flauta ;
