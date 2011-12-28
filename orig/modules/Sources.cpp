#include "Sources.h"


Sources::Sources(StkFloat jet_height, 
		 StkFloat jet_width,
		 StkFloat delta_d,
		 StkFloat flue_labium_distance,
		 StkFloat labium_position )
{


  /*****************************
   * TURBULENCE   INITIALIZATION *
   *****************************/
  my_Turbulence = new Turbulence();
  
  /*****************************
   * VORTEX   INITIALIZATION *
   *****************************/
  my_Vortex = new Vortex();
  
  /*****************************
   * JetDrive   INITIALIZATION *
   *****************************/
  my_JetDrive = new JetDrive(jet_height, 
			     jet_width,
			     delta_d,
			     flue_labium_distance,
			     labium_position  );
 
  jet_drive = 0;
  hyd_feedback = 0;
  turbulence = 0;
  vortex = 0;

}

Sources::~Sources(){    
  delete my_Turbulence;
  delete my_Vortex;
  delete my_JetDrive;
}

void Sources::clear(){
  my_Turbulence->clear();
  my_JetDrive->clear();
}

void Sources::noteOff()
{
  my_JetDrive->noteOff();
  my_Turbulence->noteOff();
  //clear();//??
}


StkFloat Sources::tick(StkFloat Jet_displacement, 
		       StkFloat Uj,
		       StkFloat mouth_acoustic_velocity,
		       StkFloat &hyd_feed)
{
  jet_drive = my_JetDrive->tick(Jet_displacement, Uj, hyd_feedback);
  turbulence = my_Turbulence->tick(Uj,my_JetDrive->get_jet_height());
  vortex = my_Vortex->tick(mouth_acoustic_velocity);

  //Filling out the output
  hyd_feed = hyd_feedback;
 return( jet_drive + turbulence + vortex);
}


StkFloat Sources::get_Hyd_feedback()
{
  return(hyd_feedback);
}

  
void Sources::set_vortex_ampli_1(StkFloat gain)
{
  my_Vortex->set_vortex_ampli_1(gain);
}


void Sources::set_vortex_ampli_2(StkFloat gain)
{
  my_Vortex->set_vortex_ampli_2(gain);
}

void Sources::set_turbulence_gain(StkFloat gain)
{
  my_Turbulence->set_turbulence_gain(gain);
}

void Sources::set_delta_d(StkFloat gain)
{
  my_JetDrive->set_delta_d(gain);
}

void Sources::set_jet_width(StkFloat gain)
{
  my_JetDrive->set_jet_width(gain);
}

void Sources::set_jet_height(StkFloat gain)
{
  my_JetDrive->set_jet_height(gain);
}

void Sources::set_jet_shape(StkFloat gain)
{
  my_JetDrive->set_b_constant(gain);
}

void Sources::set_labium_position(StkFloat gain)
{
  my_JetDrive->set_labium_position(gain);
}

void Sources::set_flue_labium_distance(StkFloat value)
{
  my_JetDrive->set_flue_labium_distance(value);
}

StkFloat Sources::get_jet_drive()
{
  return(jet_drive);
}

StkFloat Sources::get_vortex()
{
  return(vortex);
}

StkFloat Sources::get_turbulence()
{
  return(turbulence);
}

StkFloat Sources::get_FlowIn()
{
  return(my_JetDrive->get_FlowIn());
}

