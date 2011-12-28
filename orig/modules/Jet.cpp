#include "Jet.h"


Jet::Jet(StkFloat min_jet_vel,
	 StkFloat max_jet_vel,
	 StkFloat _step_Uj,
	 StkFloat flue_labium_d,
	 StkFloat max_flue_labium_d,
	 StkFloat convection_f,
	 StkFloat min_convection_f,
	 StkFloat jet_h
	 ):
  min_jet_velocity(min_jet_vel),
  max_jet_velocity(max_jet_vel),
  step_Uj(_step_Uj),
  flue_labium_dist( flue_labium_d),
  max_flue_labium_dist( max_flue_labium_d),
  convection_factor(convection_f),
  min_convection_factor(min_convection_f),
  jet_height(jet_h)
{

  /*------------------------------*
   *     General parameters       *
   *------------------------------*
   */
  sampling_frequency =  Stk::sampleRate();
  sampling_period = 1.0/sampling_frequency;
  
  /*****************************
   * Receptivity   INITIALIZATION *
   *****************************/
  my_Receptivity = new Receptivity(jet_height, flue_labium_dist);
  //  max_jet_velocity = my_Receptivity->get_maxUj();
  //  step_Uj_jet_coeff = my_Receptivity->get_stepUj();



  /*------------------------------*
   *     Jet Delay                *
   *------------------------------*
   */

  length_delay_line = floor((max_flue_labium_dist/
			     (min_convection_factor*min_jet_velocity))/
			    sampling_period);

  jetDelay = new DelayL(length_delay_line,(int)length_delay_line);
  jetDelayUj = new DelayL(length_delay_line,(int)length_delay_line);
  // jetDelayUj_steady = new DelayL(length_delay_line,(int)length_delay_line);

  jet_msamples_per_sec = flue_labium_dist/(convection_factor*sampling_period);
 

  Jet_displacement = 0;
  Delayed_Jet_displacement = 0;
  Delayed_Uj = 0;
  new_length_delay_line = length_delay_line;
  last_Uj = 1;
  //  noteOn_flag = 0;//initialize off 
}

Jet::~Jet(){  
  delete my_Receptivity;
  delete jetDelay;
  delete jetDelayUj;
  //delete jetDelayUj_steady;
}

void Jet :: change_delay_length(StkFloat Uj_steady)
{
  
  /**************************************
   *	Determine the new length of the *
   *	jet delay line in samples       *
   **************************************/
  new_length_delay_line = jet_msamples_per_sec/ Uj_steady;
  if (new_length_delay_line < 0.5){
    new_length_delay_line = 0.5;
  }
  if (new_length_delay_line > (int)length_delay_line){
    new_length_delay_line = (int)length_delay_line;
  }  
  /********************************
   * Adjusting the length of the  * 
   * jet delay                    *
   ********************************/
  
  jetDelay->setDelay(new_length_delay_line);
  jetDelayUj->setDelay(new_length_delay_line);
  //jetDelayUj_steady->setDelay(new_length_delay_line);
  
  /**************************************
   *    If changes in the jet velocity  *
   *    are bigger that the defined step*
   *    the jet delay is adjusted and   *
   *    the filter coeffs changed       *
   **************************************/
  StkFloat delta_jet_velocity = fabs(Uj_steady - last_Uj);
  if ( delta_jet_velocity > step_Uj)
    { 
      
      /********************************
       * Now I need to change the     *
       * parameters on the Receptivity*
       * filter                       *
       ********************************/
      my_Receptivity->set_Coefficients(Uj_steady);
      
      last_Uj = Uj_steady;
  
    }
}


StkFloat Jet::tick(StkFloat Vac, 
		   StkFloat Uj, 
		   StkFloat Uj_steady, 
		   StkFloat Hyd_feedback, 
		   StkFloat &del_uj)
{
  
  /************************************
   * Calculating the jet displacement * 
   ************************************/
  Jet_displacement = my_Receptivity->tick(Vac, Hyd_feedback);
  
  
  /********************************
   * Delaying the displacement &Uj * 
   ********************************/
  this->change_delay_length(Uj_steady);
  Delayed_Jet_displacement = jetDelay->tick(Jet_displacement);
  Delayed_Uj = jetDelayUj->tick(Uj);
  
  //Filling out the output
  del_uj = Delayed_Uj;
  return(Delayed_Jet_displacement);
  
}


void Jet::set_Receptivity_FilterGain(StkFloat gain)
{
 my_Receptivity->set_FilterGain(gain);
}



void Jet::set_flue_labium_dist(StkFloat dist)
{
   flue_labium_dist = dist;
   jet_msamples_per_sec = flue_labium_dist/(convection_factor*sampling_period);
}

StkFloat Jet::get_flue_labium_dist()
{
  return flue_labium_dist;
}

StkFloat Jet::get_maxUj()
{
  return(my_Receptivity->get_maxUj());
}

StkFloat Jet::get_stepUj()
{
  return(my_Receptivity->get_stepUj());
}

StkFloat Jet::get_delayedUj()
{
  return(Delayed_Uj);
}

void Jet::noteOn()
{
  //  noteOn_flag = 1;
}

void Jet::noteOff()
{
  my_Receptivity->noteOff();
  //noteOn_flag = 0;
}

void Jet::clear()
{
  jetDelay->clear();
  jetDelayUj->clear();
  //  jetDelayUj_steady->clear();
}
