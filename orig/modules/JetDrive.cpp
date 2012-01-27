#include "JetDrive.h"

JetDrive::JetDrive(StkFloat jet_h,
		   StkFloat jet_w,
		   StkFloat d_d,
		   StkFloat flue_labium_d,
		   StkFloat labium_p):delta_d(d_d),
				      labium_position(labium_p)
  
{


  /*
   *---------------------------*
   *     INITIALIZATION        *
   *---------------------------*
   */

  sampling_period = 1/Stk::sampleRate();
  current_jetdrive = 0;
  Qin = 0;
  previous_Qin = 0;
  Hyd_feedback = 0;
  b_constant = 0.5;//.39 proportion between b and jet_height

  this->update_b();
  this->update_jet_drive_constant();
  this->update_Hyd_constant();
  this->set_jet_width(jet_w);
  this->set_jet_height(jet_h);
  this->set_flue_labium_distance(flue_labium_d);





  /*
   *---------------------------*
   * TAHN_TABLE INITIALIZATION *
   *---------------------------*
   */
  max_value_tanh_table = 4.0;
  min_value_tanh_table = -max_value_tanh_table;
  step_tanh_table = 0.001;
  inv_step_tanh_table = 1.0/step_tanh_table;
  tanh_table = new Tanh_table(min_value_tanh_table, max_value_tanh_table, step_tanh_table);
  

}

JetDrive::~JetDrive(){  
  //  delete Jet_drive_filter;
  delete tanh_table;  
}

void JetDrive::clear(){
  //  Jet_drive_filter->clear();
}

StkFloat JetDrive :: FlowIn(StkFloat displacement , 
		   StkFloat Velocity)
{  
	/*
	 *----------------------------------------*
	 * 	Determine the flow goin in.	*
	 *        Labium position is positive	*
	 *	towards the interior of the 	*
	 *	instrument and zero is on the	*
	 *	axis (middle) of the flue exit.	*
	 *----------------------------------------*
	 */

  StkFloat tanh_argument = (displacement - this->labium_position)/b;
  StkFloat tanh_table_index = (int)((tanh_argument - this->min_value_tanh_table)*
  				    this->inv_step_tanh_table) + 1;

  StkFloat Flow = Velocity*b*jet_width*(1.0 + tanh_table->tick(tanh_table_index));
  return(Flow);  
}

void JetDrive::noteOff()
{
}


StkFloat JetDrive::tick(StkFloat Jet_displacement,
			StkFloat Uj,
			StkFloat &hyd_feed)
{

  //First calculate the jet drive
  Qin = this->FlowIn(Jet_displacement ,Uj);
  current_jetdrive = jet_drive_cst * (Qin - previous_Qin);

  //Now the Hydrodynamic feedback
  Hyd_feedback = Hyd_constant * Qin;
  hyd_feed = Hyd_feedback;
  
  //Update variables
  previous_Qin = Qin;

  return(current_jetdrive);    
}


StkFloat JetDrive::get_curr_jetDrive()
{
  return(current_jetdrive);
}

StkFloat JetDrive::get_Hyd_feedback()
{
  return(Hyd_feedback);
}


  
void JetDrive::set_delta_d(StkFloat value)
{
  delta_d = value;
  this->update_jet_drive_constant();
  this->update_Hyd_constant();
}


void JetDrive::set_jet_height(StkFloat value)
{
  //Set limit to .1 mm
  if (value < 0.0001){value = 0.0001;}
  jet_height = value;
  this->update_b();
}

StkFloat JetDrive::get_jet_height()
{
  return jet_height;
}

void JetDrive::set_b_constant(StkFloat value)
{
  //Set limit from 0.1 to 0.9
  if (value < 0.1){value = 0.1;}
  if (value > 2.9){value = 2.9;}
  b_constant = value;
  this->update_b();
}

void JetDrive::set_jet_width(StkFloat value)
{
  //Set limit to 1 mm
  if (value < 0.001){value = 0.001;}
  jet_width = value;
  this->update_jet_drive_constant();
}

void JetDrive::set_labium_position(StkFloat value)
{
  labium_position = value;
}

void JetDrive::set_flue_labium_distance(StkFloat value)
{
  //Set limit to 1 mm
  if (value < 0.001){value = 0.001;}
  flue_labium_distance = value;
  update_jet_drive_constant();
  update_Hyd_constant();
}

void JetDrive::update_Hyd_constant()
{
  StkFloat ratio = delta_d/flue_labium_distance;
  StkFloat beta = ratio + sqrt(ratio*(2 + ratio));
  StkFloat kappa = 1 + beta;
    Hyd_constant = 2*ratio*(kappa*kappa - 1)/
     (M_PI*(kappa*kappa + 1));
    //std::cout<<"Hyd_constant = "<< Hyd_constant << std::endl;
}

void JetDrive::update_jet_drive_constant()
{
  jet_drive_cst = -(AIR_DENSITY*delta_d)/(jet_width * flue_labium_distance*sampling_period);
}

void JetDrive::update_b()
{
  b = b_constant*jet_height;
}

StkFloat JetDrive::get_FlowIn()
{
 return(Qin);
}

