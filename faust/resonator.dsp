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

// common libs
import("filter.lib");
import("music.lib");

// flauta libs
import("constants.dsp");
import("params.dsp");

resonator(current_sources, impulse) = (current_sources, impulse) : (res ~ (_,_,_)) : out
with {
	
    res(end, tubeLeft, cdr, sources, impulse) = (end, sources, impulse, tubeLeft, cdr) 
         : (temp,_,_)
        <: (_,temp2,_,!)
        <: (_,temp3,!,_,_)
        <: (_,_,_,_,_,_,_,_)
        <: (temp4,!,temp5,!,!,_,!,!,!,!,!,!)
        <: (ed,temp6,_,_,_,!)
        <: (_,tubeDelayLeft,_,_,!,!,_,!,!,_)
         : (_,_,_,_,+)
     with{
        temp(end, sources, impulse) = sources + impulse/2 + end : chimneyDelayRight;

        temp2(tubeLeft, cavityRight, temp) = junction_gain * (-2 * temp + cavityRight + tubeLeft); 

        temp3(temp2, tubeLeft) = temp2 + tubeLeft : cavityDelayLeft : cavityDelayRight;

        temp4(temp, cdr, temp2, tubeLeft) = temp2 + cdr + tubeLeft - temp : chimneyDelayLeft; 
        // TODO : use impulse as input of ed

        ed(temp4) = temp4 + impulse/2 : mouth_radiation_filter : endDelay; 

        temp5(cavityRight, temp2) = temp2 + cavityRight : tubeDelayRight : visco_termic_filter; 

        temp6(temp5) = temp5 : radiation_filter; 
        //tdl(temp6) = temp6 : tubeDelayLeft; 
		
		
    };
  
    // out : acoustic_velocity, acoustic_pressure, out
    out(end,tdl,cdr,chimneyLeft,out) = 
      ONE_OVER_RHO_C * (end - chimneyLeft), // Vac
      end + chimneyLeft, // Pp
      out;

    junction_gain = -1 * (chim_radius * chim_radius) / ((chim_radius * chim_radius) + 2 * (cav_radius * cav_radius)); 

};

// delays

chimneyDelayRight = fdelay(MAX_DELAY_LENGTH , chimney_samples);
chimneyDelayLeft = fdelay(MAX_DELAY_LENGTH*2, chimney_samples);
cavityDelayRight = fdelay(MAX_DELAY_LENGTH , cavity_samples);
cavityDelayLeft = fdelay(MAX_DELAY_LENGTH*2, cavity_samples);
tubeDelayRight = fdelay(MAX_DELAY_LENGTH , tube_samples);
tubeDelayLeft = fdelay(MAX_DELAY_LENGTH*2, tube_samples);
endDelay = fdelay(MAX_DELAY_LENGTH, end_samples);

// filters

visco_termic_filter = iir((b0,b1,b2,b3),(a1,a2,a3))
with {
    a1 = -0.33623476246554;
    a2 = -0.71257915055968;
    a3 = 0.14508304017256;
    b0 = 0.83820223947141;
    b1 = -0.16888603248373;
    b2 = -0.64759781930259;
    b3 = 0.07424498608506;
};

mouth_radiation_filter = radiation_filter;

radiation_filter = iir((b0,b1,b2),(a1,a2))
with {
    a1 = -0.3587;
    a2 = -0.0918;
    b0 = -0.1254;
    b1 = -0.3237;
    b2 = -0.1003;
};


//process = resonator;
//process = res;


