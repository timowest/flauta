// common libs
import("filter.lib");
import("music.lib");

// flauta libs
import("excitation.dsp");
import("constants.dsp");
import("params.dsp");


junction(upCavity, loTube, lChimney) = (upCavity, loTube, lChimney) <: (k * (_ + _ + -2 * _),_,_,_)  : out_mix
with {

  out_mix(temp, upperCavity, lowerTube, leftChimney) = 
    (lowerTube + temp),  // to lower cavity
    (upperCavity + temp + lowerTube + (-1*leftChimney)), // to right chimney
	(upperCavity + temp); // to upper tube

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
    b3 =  0.07424498608506;
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

res = in<:(upperCavity,leftChimney,lowerTube,_,_,!,!,_,!,_):(junction,_,_,_,_):(lowerCavity,rightChimney,upperTube, _, _, _, _):out,!
with {

 in(lowerCavity, mouthReflection,lossesFilter, endReflection, excitation) = 
   (lowerCavity, mouthReflection+excitation, endReflection, mouthReflection,lossesFilter); 
 
 out(lowerCavity, rightChimney, upperTube, mouthReflection, lossesFilter, endReflection) =   
    lowerCavity,
    rightChimney,
    (upperTube),
    ONE_OVER_RHO_C*(rightChimney - mouthReflection),  // Vac
    (rightChimney + mouthReflection), // Pp
    (lossesFilter + endReflection); // out
    
};



resonator =(((((((res~_):(!,_,_,_,_,_))~_(mouthReflection)):(!,lossesFilter,_,_,_))~_):(endReflection,_,_,_))~_):(!,_,_,_);

//process = resonator;
//process = res;

