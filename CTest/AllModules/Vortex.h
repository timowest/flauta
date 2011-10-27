#ifndef _Vortex_h
#define _Vortex_h

#ifndef AIR_DENSITY
#define AIR_DENSITY 1.2
#endif

#define VORTEX_CTE -0.5*AIR_DENSITY*(1/0.36)

#include "Stk.h"

class Vortex
{

 private:

  //static const StkFloat Vortex_cte = -0.5*AIR_DENSITY*(1/0.36);
 
  StkFloat vortex_ampli_1;
  StkFloat vortex_ampli_2;
  StkFloat current_vortex;

 public:

  Vortex(StkFloat v_a1  = 0.1,
	 StkFloat v_a2 = 4.99);

  ~Vortex();
  
  StkFloat tick(StkFloat Vac);
  StkFloat get_curr_vortex();
  void set_vortex_ampli_1(StkFloat gain);
  void set_vortex_ampli_2(StkFloat gain);

};

#endif
