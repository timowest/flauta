#include "Bernoulli.h"


Bernoulli::Bernoulli(StkFloat chim_radius, StkFloat chan_length)
{
  
  sampling_rate = Stk::sampleRate();
  //sampling_rate = 44100.0;
  previous_Velocity = 0;
  Curr_Velocity = 0;
  Curr_Velocity_steady = 0;
  Impulse = 0;
  max_impulse = 500;//check this is not proper
  this->set_channel_length(chan_length);
  this->set_chimney_radius(chim_radius);
  
}

Bernoulli::~Bernoulli(){}


StkFloat Bernoulli::tick(StkFloat pressure_in,
			 StkFloat pressure_out,
			 StkFloat &uj_steady,
			 StkFloat &impulse)
{
  
  Curr_Velocity = Curr_Velocity + 
    (const_bernoulli*
     ((pressure_in - pressure_out) - (HALF_DENSITY * (Curr_Velocity * Curr_Velocity)))
     );
  
  Curr_Velocity_steady = Curr_Velocity_steady + 
    (const_bernoulli*
     (pressure_in - (HALF_DENSITY*(Curr_Velocity_steady * Curr_Velocity_steady)))
     );
  
  //  Impulse = output_impedance * (Curr_Velocity - previous_Velocity);
  Impulse = const_impulse * (Curr_Velocity - previous_Velocity);
  if( Impulse < 0.0)
    Impulse = 0.0;
  if( Impulse > max_impulse)
    Impulse = max_impulse;

/*
  if(pressure_in < pressure_out) {  //only asumming blowing from inside to outside.
    Curr_Velocity_steady = 0.0;
    Impulse = 0.0;
    Curr_Velocity = 0.0;
  } 
*/

  previous_Velocity = Curr_Velocity; 
  //Filling out the output
  uj_steady = Curr_Velocity_steady;
  impulse = Impulse;

  return(Curr_Velocity);

}


StkFloat Bernoulli::get_steady_velocity()
{
  return(Curr_Velocity_steady);
}


StkFloat Bernoulli::get_impulse()
{
    return(Impulse);
}
  
void Bernoulli::set_channel_length(StkFloat length)
{
  //Set minimum length to 1mm.
  if (length < 0.001){
    length = 0.001; 
  }
  channel_length = length;
  const_bernoulli = 1/(sampling_rate*AIR_DENSITY*channel_length);

}

void Bernoulli::set_chimney_radius(StkFloat chim_radius)
{
  //Set minimum chim_radious to 1mm.
  if (chim_radius < 0.001){
    chim_radius = 0.001; 
  }
  chimney_radius = chim_radius;
  set_const_impulse(chim_radius);
}

void Bernoulli :: set_impulse_scale(StkFloat scale)
{
  set_const_impulse(chimney_radius, scale);
  //  const_impulse = scale*const_impulse;
}

void Bernoulli :: set_const_impulse(StkFloat chim_radius, StkFloat scale)
{
  const_impulse = scale*(sampling_rate*AIR_DENSITY*0.61*chim_radius);
}
