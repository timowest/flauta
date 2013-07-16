#include "Blow.h"


Blow::Blow(StkFloat chimney_radius,
	   StkFloat channel_length,
	   StkFloat VibratoFreq,
	   StkFloat VibratoGain)
{

  /*****************************
   * ENVELOPE   INITIALIZATION *
   *****************************/
  my_envelope  = new ADSR;
  my_envelope->setAllTimes((StkFloat) 0.005, (StkFloat) 0.01, (StkFloat) 1.0, (StkFloat) 0.01);
  
  /*****************************
   * BERNOULLI   INITIALIZATION *
   *****************************/
  my_Bernoulli = new Bernoulli(chimney_radius, channel_length);
  vibrato = new SineWave;
  vibrato->setFrequency(VibratoFreq);
  vibratoGain = VibratoGain; // Breath periodic vibrato component.


  driving_pressure = 0;
  target_driving_pressure = 32;
  Uj = Uj_steady = Impulse = 0;
}

Blow::~Blow(){   
  delete my_Bernoulli;
  delete my_envelope; 
  delete vibrato;
}


StkFloat Blow::tick(StkFloat mouth_pressure, StkFloat &uj_steady, StkFloat &impulse)
{
    driving_pressure = target_driving_pressure; 
    //driving_pressure = my_envelope->tick() * target_driving_pressure;
    //driving_pressure += driving_pressure * ( vibratoGain * vibrato->tick());


  if( driving_pressure <= 0.0){
    driving_pressure = 0.0;
    //    std::cout<<"driving pressure inside Blow is smaller than 0, setting it to zero"<<std::endl;
  }

  Uj = my_Bernoulli->tick(driving_pressure, mouth_pressure, Uj_steady, Impulse);
  //  Uj_steady = my_Bernoulli->get_steady_velocity();
  
  // Check for the velocity and pressure limits
  // We only need to verify that is not negative here
  // Jet should take care that it doesn't pass the allowed thresholds

  if (Uj <= 0.0){
    Uj = 0.0; 	/* No negative jet velocity allowed */
  }
  
  if (Uj_steady <= 0.0){
    Uj_steady = 0.0; 	/* No negative jet velocity allowed */
  }
  
  //Filling out the output
  uj_steady = Uj_steady;
  impulse = Impulse;

  return(Uj);

}


StkFloat Blow::get_steady_velocity()
{
  return(Uj_steady);
}



StkFloat Blow::get_impulse()
{
return my_Bernoulli->get_impulse();
}


  
void Blow::set_channel_length(StkFloat length)
{
  my_Bernoulli->set_channel_length(length);
}


void Blow::noteOn(StkFloat amp)
{
  setPressure(amp);
  my_envelope->keyOn();
}

void Blow::setPressure(StkFloat amp)
{
 target_driving_pressure = amp;
}

StkFloat Blow :: get_Pressure()
{
  return target_driving_pressure;
  //make sure that is not driving_pressure that we need..
}

void Blow::noteOff(StkFloat time)
{
  //  std::cout<< "Time is %f"<< time << std::endl;
  my_envelope->setReleaseTime(time);
  my_envelope->keyOff();
  //  target_driving_pressure = 0;
}

void Blow::setReleaseRate(StkFloat amp)
{
  my_envelope->setReleaseRate(amp);
}


void Blow::set_vibrato_frequency(StkFloat freq)
{
  vibrato->setFrequency(freq);
}

void Blow::set_vibrato_gain(StkFloat gain)
{    
  vibratoGain = (gain);
}


void Blow::setAttackTime(StkFloat time)
{
  my_envelope->setAttackTime(time);
}

void Blow::setReleaseTime(StkFloat time)
{
  my_envelope->setReleaseTime(time);
}

void Blow::set_chimney_radius(StkFloat chim_radius)
{
  my_Bernoulli->set_chimney_radius(chim_radius);
}

void Blow :: set_impulse_scale(StkFloat scale)
{
  my_Bernoulli->set_impulse_scale(scale);
}

