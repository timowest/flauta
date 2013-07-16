#include "Turbulence.h"


Turbulence::Turbulence()
{
  /*
   *------------------------------------*
   *	Filter coefficients for		*	 
   *	the turbulence noise.		*
   *------------------------------------*
   */
  StkFloat a1_n, a2_n, a3_n, b1_n, b2_n, b3_n;
  a1_n = 1.0;
  a2_n = -1.59164698202301;
  a3_n = 0.69491246133220;
  b1_n = 0.15254376933390;
  b2_n = 0.0;
  b3_n = -0.15254376933390;

  StkFloat B_n_Coeffs[3]= {b1_n, b2_n, b3_n};
  StkFloat A_n_Coeffs[3]= {a1_n, a2_n, a3_n};
  //  std::vector<double> A_n_vector(A_n_Coeffs, A_n_Coeffs + 3);
  //  std::vector<double> B_n_vector(B_n_Coeffs, B_n_Coeffs + 3);
      
  //  noise_filter = new MyFilter(B_n_vector,A_n_vector);
  noise_filter = new MyFilter(3, B_n_Coeffs,3, A_n_Coeffs);
  turbulence_gain = 1;
}

Turbulence::~Turbulence(){  
  delete noise_filter;
}

void Turbulence::clear(){
  noise_filter->clear();
}

StkFloat Turbulence::tick(StkFloat Uj, StkFloat h)
{

  random_sample = 2*(((StkFloat)random()/RAND_MAX) - 0.5);//between -1,1 
//  current_turbulence = turbulence_gain * MAX_AMPLITUDE * Uj * Uj * h * noise_filter->tick(random_sample);
  current_turbulence = turbulence_gain * MAX_AMPLITUDE * Uj * Uj * h * noise_filter->tick(1);

  return(current_turbulence);

}


StkFloat Turbulence::get_curr_turbulence()
{
  return(current_turbulence);
}

  
void Turbulence::set_turbulence_gain(StkFloat gain)
{
  // turbulence_gain = gain * 7.5614e5;//(1/(.0012^2))this is to compensate h^2 in the gain... without it should be 1!;
 turbulence_gain = gain * 833;//(1/(.0012)this is to compensate h^2 in the gain... without it should be 1!;
}


void Turbulence::noteOff()
{
  //clear();??
}
