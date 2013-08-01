#ifndef _JetDrive_h
#define _JetDrive_h

#ifndef AIR_DENSITY
#define AIR_DENSITY 1.2
#endif

#include "Stk.h"
#include "Tanh_table.h"
//#include "MyFilter.h"

class JetDrive
{

 private:

    Tanh_table *tanh_table; 
    //    MyFilter *Jet_drive_filter;
    StkFloat min_value_tanh_table;
    StkFloat max_value_tanh_table;
    StkFloat step_tanh_table;
    StkFloat inv_step_tanh_table;

    StkFloat jet_drive_cst;

    StkFloat mouth_surface;

    StkFloat  jet_height;
    StkFloat  jet_width;
    StkFloat  delta_d;
    StkFloat  flue_labium_distance;
    StkFloat  labium_position;

    StkFloat  b_constant;
    StkFloat  b;


    StkFloat sampling_period;

    StkFloat Qin;
    StkFloat previous_Qin;
    StkFloat Hyd_feedback;
    StkFloat Hyd_constant;

    StkFloat current_jetdrive;

    void update_Hyd_constant();
    void update_jet_drive_constant();
    void update_b();
 public:

    JetDrive( StkFloat jet_h = 2.0e-3,
	      StkFloat jet_w = 0.02,
	      StkFloat d_d = 1.0e-3,
	      StkFloat flue_labium_d = 1.0e-2,
	      StkFloat labium_p = 0.0001
);

  ~JetDrive();

  StkFloat FlowIn(StkFloat displacement , 
		  StkFloat Velocity);
  StkFloat tick(StkFloat Jet_displacement,
		StkFloat Uj,
		StkFloat& hyd_feed);
  StkFloat get_curr_jetDrive();
  StkFloat get_Hyd_feedback();
  StkFloat get_FlowIn();

  void clear();
  void noteOff();
  void set_delta_d(StkFloat delta);
  void set_b_constant(StkFloat value);
  void set_jet_height(StkFloat value);
  void set_jet_width(StkFloat value);
  void set_labium_position(StkFloat value);
  void set_flue_labium_distance(StkFloat value);
  StkFloat get_jet_height();

};

#endif
