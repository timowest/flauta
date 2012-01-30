#ifndef _Sources_h
#define _Sources_h

#include "Stk.h"
#include <stdlib.h>
#include "Turbulence.h"
#include "Vortex.h"
#include "JetDrive.h"

class Sources
{

 private:
  Turbulence *my_Turbulence;
  Vortex *my_Vortex;
  JetDrive *my_JetDrive;
  StkFloat jet_drive;
  StkFloat hyd_feedback;
  StkFloat turbulence;
  StkFloat vortex;
 public:

  Sources(StkFloat jet_height = 1.08e-3, 
	  StkFloat jet_width = 0.02,
	  StkFloat delta_d = 1.0e-3,
	  StkFloat flue_labium_distance = 4.0e-3,
	  StkFloat labium_position = 0.0002);

  ~Sources();
  
  StkFloat tick(StkFloat Jet_displacement, 
		StkFloat Uj,
		StkFloat mouth_acoustic_velocity,
		StkFloat &hyd_feed);
  StkFloat get_Hyd_feedback();

  void clear();
  void noteOff();
  void set_vortex_ampli_1(StkFloat gain);
  void set_vortex_ampli_2(StkFloat gain);
  void set_turbulence_gain(StkFloat gain);
  void set_delta_d(StkFloat gain);    
  void set_jet_width(StkFloat gain);
  void set_jet_height(StkFloat gain);
  void set_jet_shape(StkFloat gain);
  void set_labium_position(StkFloat gain);
  void set_flue_labium_distance(StkFloat value);

  StkFloat get_jet_drive();
  StkFloat get_vortex();
  StkFloat get_turbulence();
  StkFloat get_FlowIn();
};

#endif
