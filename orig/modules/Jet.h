#ifndef _Jet_h
#define _Jet_h

#ifndef AIR_DENSITY
#define AIR_DENSITY 1.2
#endif

#include "Stk.h"
#include "DelayL.h"
#include "Receptivity.h"

class Jet
{

 private:
  /*------------------------------*
   *     General parameters       *
   *------------------------------*
   */
  StkFloat sampling_frequency;
  StkFloat sampling_period;
 
  Receptivity *my_Receptivity;
  DelayL *jetDelay;
  DelayL *jetDelayUj;
  //  DelayL *jetDelayUj_steady;

  /*------------------------------*
   *     Jet Delay                *
   *------------------------------*
   */
 
  StkFloat min_jet_velocity;
  StkFloat max_jet_velocity; 
  StkFloat step_Uj; 
  StkFloat flue_labium_dist; 
  StkFloat max_flue_labium_dist; 
  StkFloat convection_factor;
  StkFloat min_convection_factor;
  StkFloat jet_height;
  StkFloat length_delay_line;
  StkFloat jet_msamples_per_sec;
  
  StkFloat new_length_delay_line;  

  StkFloat Jet_displacement;
  StkFloat Delayed_Jet_displacement;
  StkFloat Delayed_Uj;
  StkFloat last_Uj;

   

   //   int noteOn_flag;//initialize off
   void change_delay_length(StkFloat Uj_steady);

 public:

  Jet(StkFloat min_jet_vel = 1.0 ,
      StkFloat max_jet_vel = 40,
      StkFloat _step_Uj = 1e-1,
      StkFloat flue_labium_d = 4e-3 ,
      StkFloat max_flue_labium_d = 0.016,
      StkFloat convection_f = 0.3,
      StkFloat min_convection_f = 0.3,
      StkFloat jet_h = 1.08e-3); // was 1e-3

  ~Jet();
  
  StkFloat tick(StkFloat Vac, StkFloat Uj, StkFloat Uj_steady, StkFloat Hyd_feedback, StkFloat &del_uj);
  void set_Receptivity_FilterGain(StkFloat gain);
  void set_flue_labium_dist(StkFloat dist);
  StkFloat get_flue_labium_dist();
  void noteOn();
  void noteOff();
  void clear();
  StkFloat get_maxUj();
  StkFloat get_stepUj();
  StkFloat get_delayedUj();
};

#endif
