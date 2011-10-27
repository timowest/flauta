#ifndef _Turbulence_h
#define _Turbulence_h

#ifndef AIR_DENSITY
#define AIR_DENSITY 1.2
#endif

#define MAX_AMPLITUDE 1.2e-4*0.5*AIR_DENSITY

#include "Stk.h"
#include "MyFilter.h"
#include <stdlib.h>

class Turbulence
{

 private:
  //  static const  StkFloat max_amplitude = 1.2e-4*0.5*AIR_DENSITY;
  StkFloat current_turbulence;
  StkFloat turbulence_gain;
  StkFloat random_sample;
  MyFilter *noise_filter;
 
 public:

  Turbulence();

  ~Turbulence();
  
  StkFloat tick(StkFloat Uj, StkFloat h);
  StkFloat get_curr_turbulence();
  void set_turbulence_gain(StkFloat gain);
  void clear();
  void noteOff();
};

#endif
