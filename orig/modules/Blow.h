#ifndef _Blow_h
#define _Blow_h

#ifndef AIR_DENSITY
#define AIR_DENSITY 1.2
#endif

#include "Stk.h"
#include "Bernoulli.h"
#include "ADSR.h"
#include "SineWave.h"


class Blow
{

 private:

  Bernoulli *my_Bernoulli;
  ADSR *my_envelope; 
  StkFloat driving_pressure;
  StkFloat target_driving_pressure;
  StkFloat Uj;
  StkFloat Uj_steady;
  StkFloat Impulse;
  SineWave *vibrato;
  StkFloat vibratoGain;


 public:

  Blow(StkFloat chimney_radius = 0.007,
       StkFloat channel_length = 1e-2,
       StkFloat VibratoFreq = 5.9,
       StkFloat VibratoGain = 0.0);

  ~Blow();
  
  StkFloat tick(StkFloat mouth_pressure, StkFloat &uj_steady, StkFloat &impulse);
  StkFloat get_steady_velocity();
  StkFloat get_impulse();
  void set_channel_length(StkFloat length);
  void noteOn(StkFloat amp);
  void noteOff(StkFloat time);
  void setPressure(StkFloat amp);
  StkFloat get_Pressure();
  void setReleaseRate(StkFloat amp);
  void set_vibrato_frequency(StkFloat freq);
  void set_vibrato_gain(StkFloat gain);
  void setAttackTime(StkFloat time);
  void setReleaseTime(StkFloat time); 
  void set_impulse_scale(StkFloat scale);
 void set_chimney_radius(StkFloat chim_radius); 
};

#endif
