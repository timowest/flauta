#include "Excitation.h"
//#include <iostream.h>

Excitation::Excitation(StkFloat min_jet_vel,
		       StkFloat max_jet_vel,
		       StkFloat step_Uj,
		       StkFloat flue_labium_distance,
		       StkFloat max_flue_labium_d,
		       StkFloat labium_position,
		       StkFloat convection_f,
		       StkFloat min_convection_f,
		       StkFloat chimney_radius,
		       StkFloat channel_length,
		       StkFloat VibratoFreq,
		       StkFloat VibratoGain,
		       StkFloat jet_height, 
		       StkFloat jet_width,
		       StkFloat delta_d):
  min_jet_velocity(min_jet_vel),max_jet_velocity(max_jet_vel)
  
{

  
  /*****************************
   * Jet   INITIALIZATION *
   *****************************/
  my_Jet = new Jet(min_jet_vel,
		   max_jet_vel,
		   step_Uj,
		   flue_labium_distance,
		   max_flue_labium_d,
		   convection_f,
		   min_convection_f,
		   jet_height
		   );
 
  /*****************************
   * Blow   INITIALIZATION *
   *****************************/
  my_Blow = new Blow(chimney_radius,
		     channel_length,
		     VibratoFreq,
		     VibratoGain);
  
  //  cout<< max_Uj_jet_coeff << endl << mouth_impedance <<endl;
  /*****************************
   * Sources   INITIALIZATION *
   *****************************/
  my_Sources = new Sources( jet_height, 
			    jet_width,
			    delta_d,
			    flue_labium_distance,
			    labium_position);


  /*------------------------------*
   *     Operational parameters     *
   *------------------------------*
   */

  Uj= 0;
  Uj_steady = 0;
  Jet_displacement = 0;
  current_impulse = 0;
  Hyd_feedback = Previous_Hyd_feedback = 0;
}

Excitation::~Excitation(){  
  delete my_Jet;
  delete my_Blow;
  delete my_Sources;
}


StkFloat Excitation::tick(StkFloat mouth_acoustic_pressure,
			  StkFloat mouth_acoustic_velocity,
			  StkFloat &impulse)
{
  StkFloat  delayedUj;
  
  
  /**************************************
   *	First tick the Blow     	*
   **************************************/

  Uj = my_Blow->tick(mouth_acoustic_pressure, Uj_steady, current_impulse);
  
  /**************************************
   *	Checking variable boundaries	*
   **************************************/
  
  if(Uj < min_jet_velocity)
    Uj = min_jet_velocity;
  
  if(Uj > max_jet_velocity)
    Uj = max_jet_velocity;
  
  if(Uj_steady < min_jet_velocity)
    Uj_steady = min_jet_velocity;
  
  if(Uj_steady > max_jet_velocity)
    Uj_steady = max_jet_velocity;
  

  //Hydrodynamic feedback before ticking the jet
  //Hyd_feedback = my_Sources->get_Hyd_feedback();

  //Jet calculates the jet displacement and delayed Uj
  Jet_displacement = my_Jet->tick(mouth_acoustic_velocity,Uj, Uj_steady, Previous_Hyd_feedback, delayedUj);


  /********************************
   * We need to use a delayed     *
   * version of Uj to calculate   *
   * Qin, jetdrive and the sources*
   ********************************/

  //  delayedUj = my_Jet->get_delayedUj();
  last_Output = my_Sources->tick(Jet_displacement, delayedUj,mouth_acoustic_velocity, Hyd_feedback); 
  Previous_Hyd_feedback = Hyd_feedback;				     

  //Filling out the output
  impulse = current_impulse;
  return(last_Output);

}


StkFloat Excitation::last_Out()
{
  return(last_Output);
}

  
void Excitation::set_vortex_ampli_1(StkFloat gain)
{
 my_Sources->set_vortex_ampli_1(gain);
}

void Excitation::set_vortex_ampli_2(StkFloat gain)
{
 my_Sources->set_vortex_ampli_2(gain);
}

void Excitation::set_turbulence_gain(StkFloat gain)
{
 my_Sources->set_turbulence_gain(gain);
}

void Excitation::set_delta_d(StkFloat gain)
{
 my_Sources->set_delta_d(gain);
}

void Excitation::set_jet_width(StkFloat gain)
{
 my_Sources->set_jet_width(gain);
}

void Excitation::set_jet_shape(StkFloat gain)
{
 my_Sources->set_jet_shape(gain);
}


void Excitation::set_jet_height(StkFloat gain)
{
 my_Sources->set_jet_height(gain);
}

void Excitation::set_labium_position(StkFloat gain)
{
 my_Sources->set_labium_position(gain);
}

void Excitation::set_flue_labium_dist(StkFloat gain)
{
 my_Jet->set_flue_labium_dist(gain);
 my_Sources->set_flue_labium_distance(gain);
}

StkFloat Excitation::get_flue_labium_dist()
{
  return my_Jet->get_flue_labium_dist();
}

void Excitation::set_vibrato_gain(StkFloat gain)
{
 my_Blow->set_vibrato_gain(gain);
}

void Excitation::set_vibrato_frequency(StkFloat gain)
{
 my_Blow->set_vibrato_frequency(gain);
}


void Excitation::set_channel_length(StkFloat gain)
{
 my_Blow->set_channel_length(gain);
}

StkFloat Excitation::get_Uj()
{
  return(Uj);
}

StkFloat Excitation::get_Uj_steady()
{
  return(Uj_steady);
}

StkFloat Excitation::get_jet_drive()
{
  return(my_Sources->get_jet_drive());
}

StkFloat Excitation::get_vortex()
{
  return(my_Sources->get_vortex());
}

StkFloat Excitation::get_turbulence()
{
  return(my_Sources->get_turbulence());
}

StkFloat Excitation::get_impulse()
{
  return(current_impulse);
}

StkFloat Excitation::get_Hyd_feedback()
{
  return(my_Sources->get_Hyd_feedback());
}

StkFloat Excitation::get_Jet_displacement()
{
  return(Jet_displacement);
}


StkFloat Excitation::get_FlowIn()
{
  return(my_Sources->get_FlowIn());
}


void Excitation :: noteOn(StkFloat amp)
{
  my_Blow->noteOn(amp);
  my_Jet->noteOn();
};

void Excitation :: setPressure(StkFloat amp)
{
  my_Blow->setPressure(amp);
};

StkFloat Excitation :: get_Pressure()
{
  return my_Blow->get_Pressure();
}

void Excitation :: noteOff(StkFloat time){
  //  my_Blow->setReleaseRate(rate * 0.02);
  my_Blow->noteOff(time);
  my_Jet->noteOff();
  //  my_Sources->noteOff();
};

void Excitation::setAttackTime(StkFloat time)
{
  my_Blow->setAttackTime(time);
}

void Excitation::setReleaseTime(StkFloat time)
{
  my_Blow->setReleaseTime(time);
}

void Excitation :: set_impulse_scale(StkFloat scale)
{
  my_Blow->set_impulse_scale(scale);
}
