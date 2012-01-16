#ifndef _Resonator_h
#define _Resonator_h

#include "Stk.h"
#include "DelayL.h"
//#include "DelayL_fade.h"
#include "MyFilter.h"

#define	SOUND_SPEED 	343.54
#define TWO_SOUND_SPEED  687.08
#define AIR_DENSITY	1.2
#define ONE_OVER_RHO_C 1.0/(AIR_DENSITY * SOUND_SPEED)
#define MAX_DELAY_LENGTH 10000
#define RAD_ORDER 3
#define VT_ORDER 4

class Resonator
{

 private: 

  DelayL *chimneyDelayRight;  
  DelayL *chimneyDelayLeft;
  DelayL *cavityDelayRight;  
  DelayL *cavityDelayLeft;
  DelayL *tubeDelayRight;  
  DelayL *tubeDelayLeft;
  DelayL *endDelay;


  MyFilter *visco_thermic_filter;
  MyFilter *radiation_filter;
  MyFilter *mouth_radiation_filter;

   /*------------------------------*
   *     Geometric parameters     *
   *------------------------------*
   */
  StkFloat last_Output;
  StkFloat sampling_frequency;
  StkFloat sampling_period;
  //Embouchure Cavity 
  StkFloat   cavity_length;
  StkFloat   cavity_radius;
  StkFloat   cavity_samples;
  
  //Embouchure Chimney
  StkFloat   chimney_length;
  StkFloat   chimney_radius;
  StkFloat   chimney_samples;
  
  //Embouchure end correction
  StkFloat    end_corr_length;
  StkFloat    end_corr_radius;
  StkFloat    end_corr_samples;
  
 //Tube
  StkFloat   tube_length;
  StkFloat   tube_radius;
  StkFloat   tube_samples;
  
  //Junction
  StkFloat   junction_gain;

  //filter flags
  bool  radiation_flag;
  bool  visco_thermic_flag;

 public:

  Resonator(StkFloat cav_length = .0175,
	    StkFloat cav_radius = 0.0085,
	    StkFloat chim_length = 0.01,
	    StkFloat chim_radius = 0.007,
	    StkFloat end_length = 0.08,
	    StkFloat end_radius = 0.007,
	    StkFloat tub_length = 0.245,
	    StkFloat tub_radius = 0.009
);

  ~Resonator();
  
  StkFloat tick(StkFloat current_sources, StkFloat impulse);
  StkFloat get_mouth_acoustic_pressure();
  StkFloat get_acoustic_velocity();
  StkFloat get_impedance();

  void noteOn(StkFloat freq);
  void noteOff();
  void clear();
  void set_tube_delay(StkFloat delay);
  void set_cavity_delay(StkFloat delay);
  void set_cavity_length(StkFloat length);
  void set_chimney_delay(StkFloat delay);
  void set_chimney_length(StkFloat length);
  void set_end_delay(StkFloat delay);
  void set_end_length(StkFloat length);
  
  void setFrequency(StkFloat freq);
  StkFloat get_frequency();
  StkFloat radiation_tick(StkFloat in);
  StkFloat visco_thermic_tick(StkFloat in);
  void set_radiation_flag(bool flag);
  void set_visco_thermic_flag(bool flag);
  StkFloat check_boundaries(StkFloat value);


};

#endif
