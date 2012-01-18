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

// TODO : move flauta and process declarations to flauta.dsp when this is ready

// flauta
flauta = (excitation : resonator) ~ (_,_) : (!,!,_);

/*flauta = ((((excitation : resonator) ~ _) : (!,_,_)) ~ _) : (!,_);*/

process = flauta;

// common libs
import("filter.lib");
import("music.lib");

// flauta libs
import("excitation.dsp");
import("constants.dsp");
import("params.dsp");

resonator = (((((((res~_)
    : (!,_,_,_,_,_)) ~ _(mouthReflection))
    : (!,lossesFilter,_,_,_)) ~ _)
    : (endReflection,_,_,_)) ~ _) 
    : (!,_,_,_);

// out : lowerCavity, rightChimney, upperTube, Vac, Pp, out
res(lowCav, mouRef, losFil, endRef, sour, imp) =  
    (lowCav, mouRef, losFil, endRef, sour, imp) <: (_,_,!,!,_,_,!,!,!,_,!,!,!,_,_,!,!,!)
    //(lowCav, mouRef+(sour+imp/2), endRef, mouRef,losFil) 
    : (_,_+_+_/2,_,_,_) 
    //first delays
    <: (upperCavity, leftChimney, lowerTube,_,_,!,!,_,!,!) 
    // junction
    : (junction,_,_,_) 
    // second delays
    : (lowerCavity, rightChimney, upperTube, _, _, _) 
    //outputs
    : out
with {

 out(lowerCavity, rightChimney, upperTube, mouthReflection, lossesFilter, endReflection) =
    lowerCavity,
    rightChimney,
    upperTube,
    ONE_OVER_RHO_C*(rightChimney - mouthReflection), // Vac
    (rightChimney + mouthReflection), // Pp
    (lossesFilter + endReflection); // out

  toVac(rightChimney) = ONE_OVER_RHO_C*(rightChimney - mouthReflection);
    
};

// mostly preserved from original definition
junction(upCavity, lChimney, loTube) = (upCavity, loTube, lChimney) <: (k * (_ + _ + -2 * _),_,_,_) : out_mix
with {

  out_mix(temp, upperCavity, lowerTube, leftChimney) =
    lowerTube + temp, // to lower cavity
    upperCavity + temp + lowerTube + (-1*leftChimney), // to right chimney
    upperCavity + temp; // to upper tube

  k = -1*((chim_radius*chim_radius))/((chim_radius*chim_radius) - 2*(cav_radius*cav_radius));

};

// delays

leftChimney = fdelay(MAX_DELAY_LENGTH, chimney_samples);
rightChimney = fdelay(MAX_DELAY_LENGTH, chimney_samples);
upperCavity = fdelay(MAX_DELAY_LENGTH, cavity_samples);
lowerCavity = fdelay(MAX_DELAY_LENGTH, cavity_samples);
upperTube = fdelay(MAX_DELAY_LENGTH, tube_samples);
lowerTube = fdelay(MAX_DELAY_LENGTH, tube_samples);
//endDelay = fdelay(MAX_DELAY_LENGTH, end_samples);

end_samples = end_length * SR / TWO_SOUND_SPEED;
cavity_samples = cav_length * SR / TWO_SOUND_SPEED;
chimney_samples = chim_length * SR / TWO_SOUND_SPEED;
tube_samples = tub_length * SR / TWO_SOUND_SPEED;

// filters

lossesFilter = iir((b0,b1,b2,b3),(a1,a2,a3))
with {
    a1 = -0.33623476246554;
    a2 = -0.71257915055968;
    a3 = 0.14508304017256;
    b0 = 0.83820223947141;
    b1 = -0.16888603248373;
    b2 = -0.64759781930259;
    b3 = 0.07424498608506;
};

mouthReflection = endReflection;

endReflection = iir((b0,b1,b2),(a1,a2))
with {
    a1 = -0.3587;
    a2 = -0.0918;
    b0 = -0.1254;
    b1 = -0.3237;
    b2 = -0.1003;
};

//process = resonator;
//process = res;


