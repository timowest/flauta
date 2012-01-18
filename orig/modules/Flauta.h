/****************************************************************/
/* transverse flute Object by Patricio de la Cuadra, Jul. 2004  */
/*                                                              */
/****************************************************************/


#if !defined(__Flauta_h)
#define __Flauta_h

#include "Stk.h"
#include "Instrmnt.h"
#include <stdlib.h>
#include <iostream>
#include "Resonator.h"
#include "Excitation.h"
#include "Skini.h"

using namespace std;

class Flauta : public Instrmnt
{
 protected:  


  Excitation *my_Excitation;
  Resonator *my_Resonator;
  /*------------------------------*
   *     General parameters       *
   *------------------------------*
   */
  StkFloat sampling_frequency;
  StkFloat last_Output;
  StkFloat DACScale;  

  /*------------------------------*
   *     Control parameters       *
   *------------------------------*
   */
  StkFloat driving_pressure;
  StkFloat coarse_pressure;
  StkFloat fine_pressure;
  //  StkFloat curr_frequency; // not sure we need to keep curr_freq as global
 

  /*------------------------------*
   *     Operational parameters     *
   *------------------------------*
   */

  StkFloat  mouth_acoustic_pressure;
  StkFloat  mouth_acoustic_velocity;

  
 public:
  Flauta(StkFloat cav_length = .0175,
	 StkFloat cav_radius = 0.0085,
	 StkFloat chim_length = 0.01,
	 StkFloat chim_radius = 0.007,
	 StkFloat end_length = 0.08,
	 StkFloat end_radius = 0.007,
	 StkFloat tub_length = 0.245,
	 StkFloat tub_radius = 0.009,
	 StkFloat min_jet_vel = 1.0 ,
	 StkFloat max_jet_vel = 40,
	 StkFloat step_Uj = .1,
	 StkFloat flue_labium_distance = 4e-3,
	 StkFloat max_flue_labium_d = 0.016,
	 StkFloat labium_position = 0.0002,
	 StkFloat convection_f = 0.5,
	 StkFloat min_convection_f = 0.3,
	 StkFloat channel_length = 4e-3,
	 StkFloat VibratoFreq = 5.9,
	 StkFloat VibratoGain = 0.0,
	 StkFloat jet_height = 1e-3, 
	 StkFloat jet_width = 0.02,
	 StkFloat delta_d = 1.0e-3);
  
  ~Flauta();
  
  void noteOn(StkFloat freq, StkFloat amp);
  void noteOff(StkFloat time);
  void setFrequency(StkFloat local_frequency);
  void controlChange(int number, StkFloat value);

  void setPressure(StkFloat pressure);
  StkFloat lastOut();
  void clear();
  StkFloat tick();
  StkFloat tick(StkFloat* output, int output_length);
  void set_vortex_ampli_1(StkFloat input_data);
  void set_vortex_ampli_2(StkFloat input_data);
  void set_turbulence_gain(StkFloat input_data);
  void set_channel_length(StkFloat input_data);
  void set_delta_d(StkFloat input_data);
  void set_jet_width(StkFloat input_data);
  void set_jet_height(StkFloat input_data);
  void set_jet_shape(StkFloat gain);
  void set_labium_position(StkFloat input_data);
  void set_flue_labium_dist(StkFloat input_data);
  void set_vibrato_gain(StkFloat input_data);
  void set_vibrato_frequency(StkFloat input_data);
  void set_DACScale(StkFloat input_data);
  void set_cavity_length(StkFloat input_data);
  void set_impulse_scale(StkFloat scale);
  void set_chimney_length(StkFloat input_data);
  void set_radiation_flag(bool flag);
  void set_visco_thermic_flag(bool flag);
  void setAttackTime(StkFloat time);
  void setReleaseTime(StkFloat time);  
  StkFloat get_frequency();
  StkFloat get_flue_labium_dist();
  StkFloat get_pressure();
  StkFloat computeSample( void );
};
  
#endif
