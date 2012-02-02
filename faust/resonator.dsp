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

/*StkFloat Resonator::tick(StkFloat current_sources, StkFloat impulse)
{

  // Propagate to the tube throught the 3 port junction
  
  StkFloat temp,temp2,temp3,temp4,temp5,temp6;

  temp = chimneyDelayRight->tick(current_sources +(impulse/2) + endDelay->lastOut());
  // the common sigma
  temp2 = junction_gain* (-2*temp + cavityDelayRight->lastOut() + tubeDelayLeft->lastOut());
  
  // The cavity
  temp3 = cavityDelayLeft->tick(temp2 + tubeDelayLeft->lastOut());
  cavityDelayRight->tick(temp3);
  
  // The chimney
  temp4 = chimneyDelayLeft->tick(temp2 + cavityDelayRight->lastOut() + tubeDelayLeft->lastOut() - temp);
  endDelay->tick(mouth_radiation_filter->tick(temp4 + impulse/2));
  // The tube
  temp5 = visco_thermic_tick(tubeDelayRight->tick(temp2 + cavityDelayRight->lastOut()));
  temp6 = radiation_tick(temp5);
  tubeDelayLeft->tick(temp6);

  // OUTPUT:
  //Reading at the embochure
  //  last_Output = endDelay->lastOut() + chimneyDelayLeft->lastOut();
  
  // Reading at the end of the tube
  last_Output = temp5 + temp6;
  return (last_Output);

}

StkFloat Resonator::get_mouth_acoustic_pressure()
{
  return(endDelay->lastOut() + chimneyDelayLeft->lastOut());
}

StkFloat Resonator::get_acoustic_velocity()
{
  return(ONE_OVER_RHO_C*(endDelay->lastOut() - chimneyDelayLeft->lastOut()));
}

*/

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


