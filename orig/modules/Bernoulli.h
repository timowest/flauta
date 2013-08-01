#ifndef _Bernoulli_h
#define _Bernoulli_h

#ifndef AIR_DENSITY
#define AIR_DENSITY 1.2
#define HALF_DENSITY AIR_DENSITY/2
#endif

#include "Stk.h"

class Bernoulli
{

 private:
  StkFloat sampling_rate;
  StkFloat channel_length;
  StkFloat const_bernoulli;
  StkFloat const_impulse;
  StkFloat chimney_radius;
 
  StkFloat previous_Velocity;
  StkFloat previous_Velocity_steady;
  StkFloat Curr_Velocity;
  StkFloat Curr_Velocity_steady;
  StkFloat Impulse;
  StkFloat max_impulse;
  
  StkFloat pressure_in;
  StkFloat pressure_out;
  
 public:

  Bernoulli(StkFloat chim_radius = 0.007,
	    StkFloat chan_length = 1e-2);

  ~Bernoulli();
  
  StkFloat tick(StkFloat pressure_in,
		StkFloat pressure_out,
		StkFloat &uj_steady,
		StkFloat &impulse);
  StkFloat get_steady_velocity();
  StkFloat get_impulse();
  void set_channel_length(StkFloat length);
  void set_chimney_radius(StkFloat chim_radius);
  void set_impulse_scale(StkFloat scale);
  void set_const_impulse(StkFloat chim_radius, StkFloat scale=1);

};


#endif
