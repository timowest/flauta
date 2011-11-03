#include "Vortex.h"


Vortex::Vortex(StkFloat v_a1,
	       StkFloat v_a2)
{

  vortex_ampli_1 = v_a1;
  vortex_ampli_2 = v_a2;
  current_vortex = 0;
}

Vortex::~Vortex(){  
}


StkFloat Vortex::tick(StkFloat Vac)
{

  if (Vac > 0.0)
    current_vortex = vortex_ampli_1*VORTEX_CTE* Vac * Vac;
  else
    current_vortex = -vortex_ampli_2*VORTEX_CTE* Vac * Vac;


  return(current_vortex);

}


StkFloat Vortex::get_curr_vortex()
{
  return(current_vortex);
}

  
void Vortex::set_vortex_ampli_1(StkFloat gain)
{
 vortex_ampli_1 = gain;
}


void Vortex::set_vortex_ampli_2(StkFloat gain)
{
 vortex_ampli_2 = gain;
}

