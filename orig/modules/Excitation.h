#ifndef _Excitation_h
#define _Excitation_h

#include "Stk.h"
#include "Jet.h"
#include "Blow.h"
#include "Sources.h"
#include <stdlib.h>

class Excitation
{

 private:

  Jet *my_Jet;
  Blow *my_Blow;
  Sources *my_Sources;

  StkFloat last_Output;
  StkFloat driving_pressure;
 
  /*------------------------------*
   *     Operational parameters     *
   *------------------------------*
   */

  StkFloat  Uj, Uj_steady;
  StkFloat Jet_displacement;
  StkFloat current_impulse;
  StkFloat min_jet_velocity, max_jet_velocity;
  StkFloat Hyd_feedback;
  StkFloat Previous_Hyd_feedback;


 public:

  Excitation(StkFloat min_jet_vel = 1.0 ,
	     StkFloat max_jet_vel = 40,
	     StkFloat step_Uj = 1e-1,
	     StkFloat flue_labium_distance = 4e-3,
	     StkFloat max_flue_labium_d = 0.016,
	     StkFloat labium_position = 0.0002,
	     StkFloat convection_f = 0.3,
	     StkFloat min_convection_f = 0.3,
	     StkFloat chimney_radius = 0.007,
	     StkFloat channel_length = 4e-3,
	     StkFloat VibratoFreq = 5.9,
	     StkFloat VibratoGain = 0.0,
	     StkFloat jet_height = 1.08e-3, 
	     StkFloat jet_width = 0.02,
	     StkFloat delta_d = 1.0e-3);

  ~Excitation();
  
  StkFloat tick(StkFloat mouth_acoustic_pressure,
		StkFloat mouth_acoustic_velocity,
		StkFloat &impulse);

  StkFloat last_Out();
  void set_vortex_ampli_1(StkFloat gain);
  void set_vortex_ampli_2(StkFloat gain);
  void set_turbulence_gain(StkFloat gain);
  void set_delta_d(StkFloat gain);
  void set_jet_width(StkFloat gain);
  void set_jet_height(StkFloat gain);
  void set_labium_position(StkFloat gain);
  void set_flue_labium_dist(StkFloat gain);
  void set_vibrato_gain(StkFloat gain);
  void set_vibrato_frequency(StkFloat gain);
  void set_channel_length(StkFloat gain);
  void set_jet_shape(StkFloat gain);
  void set_impulse_scale(StkFloat scale);
  StkFloat get_Uj();
  StkFloat get_Uj_steady();
  StkFloat get_jet_drive();
  StkFloat get_vortex();
  StkFloat get_impulse();
  StkFloat get_turbulence();
  StkFloat get_Hyd_feedback();
  StkFloat get_Jet_displacement();
  StkFloat get_FlowIn();
  StkFloat get_Pressure();
  StkFloat get_flue_labium_dist();
  void noteOn(StkFloat amp);
  void noteOff(StkFloat time);
  void setPressure(StkFloat amp);
  void setAttackTime(StkFloat time);
  void setReleaseTime(StkFloat time);  

};

#endif
