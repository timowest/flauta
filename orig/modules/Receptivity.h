#ifndef _Receptivity_h
#define _Receptivity_h

#ifndef M_PI
#define M_PI 3.141592654
#endif

#ifndef TWO_div_M_PI
#define TWO_div_M_PI 2/M_PI
#endif

#include <cmath>
#include "Stk.h"
//#include "MyTable.h"
#include "MyFilter.h"



class Receptivity
{

 private:
  MyFilter*  Jet_filter_peak1;
  MyFilter*  Jet_filter_peak2;
  MyFilter*  Jet_filter_shelf;
  MyFilter*  Jet_filter_peak1_inv;
  MyFilter*  Jet_filter_peak2_inv;
  MyFilter*  Jet_filter_shelf_inv;
  MyFilter*  Jet_fiter_one_over_omega;
  StkFloat  Jet_displacement;
  StkFloat  sampling_frequency;
  StkFloat  min_Uj;
  StkFloat  max_Uj;
  StkFloat  step_Uj;
  StkFloat jet_height;
  StkFloat flue_labium_dist;

  StkFloat  jet_ampli_cst;

  StkFloat excitation;
  StkFloat coeff_table_index;
  StkFloat lastOut;
  void calculate_peak_filter(StkFloat low_freq,
			     StkFloat high_freq,
			     StkFloat gain,
			     StkFloat *B_coeffs,
			     StkFloat *A_coeffs
			     /*std::vector<StkFloat> &B_coeffs,
			       std::vector<StkFloat> &A_coeffs*/);

  void calculate_shelf_filter(StkFloat low_gain,
			     StkFloat high_gain,
			     StkFloat transition_freq,
			     StkFloat *B_coeffs,
			     StkFloat *A_coeffs
			     /*std::vector<StkFloat> &B_coeffs,
			       std::vector<StkFloat> &A_coeffs*/);


 public:

  Receptivity(StkFloat  _jet_height = 1.08e-3,
	      StkFloat  _flue_labium_dist = 4e-3   
	      );

  ~Receptivity();
  void clear();  
  StkFloat tick(StkFloat Vac, StkFloat Qin);
  void set_Coefficients(StkFloat Uj_steady);
  void set_FilterGain(StkFloat gain);

  StkFloat get_minUj();
  StkFloat get_maxUj();
  StkFloat get_stepUj();
  void noteOff();

};

#endif
