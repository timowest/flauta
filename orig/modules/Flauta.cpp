/****************************************************************/
/* transverse flute Object by Patricio de la Cuadra, Jul. 2004  */
/*                                                              */
/****************************************************************/

#include "Flauta.h"

//#include "WvOut.h"
//WvOut *wav_out = 0;

Flauta :: Flauta(StkFloat cav_length,
		 StkFloat cav_radius,
		 StkFloat chim_length,
		 StkFloat chim_radius,
		 StkFloat end_length,
		 StkFloat end_radius,
		 StkFloat tub_length,
		 StkFloat tub_radius,
		 StkFloat min_jet_vel,
		 StkFloat max_jet_vel,
		 StkFloat step_Uj,
		 StkFloat flue_labium_distance,
		 StkFloat max_flue_labium_d,
		 StkFloat labium_position,
		 StkFloat convection_f,
		 StkFloat min_convection_f,
		 StkFloat channel_length,
		 StkFloat VibratoFreq,
		 StkFloat VibratoGain,
		 StkFloat jet_height, 
		 StkFloat jet_width,
		 StkFloat delta_d)
{

  /*------------------------------*
   *     General parameters       *
   *------------------------------*
   */
  sampling_frequency =  Stk::sampleRate();
  // wav_out = new WvOut("test", 13, WvOut::WVOUT_WAV);

  /*------------------------------*
   *     Operational parameters     *
   *------------------------------*
   */
  
  mouth_acoustic_pressure = 0.0;
  mouth_acoustic_velocity = 0.0;
  DACScale = 0.007;

  /*****************************
   * Resonator   INITIALIZATION *
   *****************************/
  my_Resonator = new Resonator( cav_length,
				cav_radius,
				chim_length,
				chim_radius,
				end_length,
				end_radius,
				tub_length,
				tub_radius);
  

  /*****************************
   * Excitation  INITIALIZATION *
   *****************************/
  my_Excitation = new Excitation( min_jet_vel,
				  max_jet_vel,
				  step_Uj,
				  flue_labium_distance,
				  max_flue_labium_d,
				  labium_position,
				  convection_f,
				  min_convection_f,
				  chim_radius,
				  channel_length,
				  VibratoFreq,
				  VibratoGain,
				  jet_height, 
				  jet_width,
				  delta_d);
  
  
};




Flauta ::  ~Flauta(){
  delete my_Resonator;
  delete my_Excitation;
  //delete wav_out;
};



void Flauta :: noteOn(StkFloat freq, StkFloat amp){
  //Frequency in Hz to make it compatible with what is sent by voicer; amp in midi number

  //Assign local variables

  //this->setdriving_pressure(amp); 
  //curr_frequency = freq;  

  my_Resonator->noteOn(freq);
  my_Excitation->noteOn(amp);

};



void Flauta :: noteOff(StkFloat time){

  my_Excitation->noteOff(time);
  my_Resonator->noteOff();

};



void Flauta :: setFrequency(StkFloat freq){
  //curr_frequency = local_frequency;
  my_Resonator->setFrequency(freq);
};

StkFloat Flauta :: get_frequency()
{
  return my_Resonator->get_frequency();
}

void Flauta :: setPressure(StkFloat pressure){
  my_Excitation->setPressure(pressure);
};
 
StkFloat Flauta :: get_pressure(){
  return my_Excitation->get_Pressure();
}

StkFloat Flauta :: lastOut(){
  return last_Output;
};



void Flauta :: clear(){};




StkFloat Flauta :: tick()
{

  StkFloat current_excitation, impulse;

  // Input variables

  this->mouth_acoustic_pressure = my_Resonator->get_mouth_acoustic_pressure();
  this->mouth_acoustic_velocity = my_Resonator->get_acoustic_velocity();


  current_excitation = my_Excitation->tick(mouth_acoustic_pressure,
					   mouth_acoustic_velocity,
					   impulse);
  
  last_Output = my_Resonator->tick(current_excitation, impulse);
 
  return(DACScale*last_Output);

}

StkFloat Flauta :: tick(StkFloat* output, int output_length)
{
  StkFloat current_excitation, impulse;

  // Input variables

  this->mouth_acoustic_pressure = my_Resonator->get_mouth_acoustic_pressure();
  this->mouth_acoustic_velocity = my_Resonator->get_acoustic_velocity();


  current_excitation = my_Excitation->tick(mouth_acoustic_pressure,
					   mouth_acoustic_velocity,
					   impulse);

  last_Output = my_Resonator->tick(current_excitation, impulse);

  //Filling up the output vector;
  if (output_length != 13){
    std::cout<<"Sorry the tick output vector must be 13 and it is" 
	     << output_length << " quitting" << std::endl;
    exit(0);
  }
  output[0] = last_Output;//current mouth pressure
  output[1] = mouth_acoustic_pressure;
  output[2] = mouth_acoustic_velocity;
  output[3] = current_excitation;
  output[4] = my_Excitation->get_Uj();
  output[5] = my_Excitation->get_Uj_steady();
  output[6] = my_Excitation->get_jet_drive();
  output[7] = my_Excitation->get_vortex();
  output[8] = impulse;
  output[9] = my_Excitation->get_turbulence();
  output[10] = my_Excitation->get_Hyd_feedback();
  output[11] = my_Excitation->get_Jet_displacement();
  output[12] = my_Excitation->get_FlowIn();

  //  wav_out->tickFrame(output);
  return(DACScale*last_Output);

    
}

void Flauta :: set_vortex_ampli_1(StkFloat input_data)
{
  my_Excitation->set_vortex_ampli_1((StkFloat) input_data);
}

void Flauta :: set_vortex_ampli_2(StkFloat input_data)
{
  my_Excitation->set_vortex_ampli_2((StkFloat) input_data);
}

void Flauta :: set_turbulence_gain(StkFloat input_data)
{
  my_Excitation->set_turbulence_gain((StkFloat) input_data);
}

void Flauta :: set_channel_length(StkFloat input_data)
{
  my_Excitation->set_channel_length((StkFloat)input_data);
}

void Flauta :: set_delta_d(StkFloat input_data)
{
  my_Excitation->set_delta_d((StkFloat)input_data);
}

void Flauta :: set_jet_width(StkFloat input_data)
{
  my_Excitation->set_jet_width((StkFloat)input_data);
}

void Flauta :: set_jet_height(StkFloat input_data)
{
  my_Excitation->set_jet_height((StkFloat)input_data);
}

void Flauta :: set_jet_shape(StkFloat gain)
{
  my_Excitation->set_jet_shape((StkFloat)gain);
}

void Flauta :: set_labium_position(StkFloat input_data)
{
  my_Excitation->set_labium_position((StkFloat)input_data);
}

void Flauta :: set_flue_labium_dist(StkFloat input_data)
{
  my_Excitation->set_flue_labium_dist((StkFloat)input_data);
}

StkFloat Flauta :: get_flue_labium_dist()
{
  return my_Excitation->get_flue_labium_dist();
}

void Flauta :: set_vibrato_gain(StkFloat input_data)
{
  my_Excitation->set_vibrato_gain( input_data);
}

void Flauta :: set_vibrato_frequency(StkFloat input_data)
{
  my_Excitation->set_vibrato_frequency(input_data);
}

void Flauta :: set_DACScale(StkFloat input_data)
{
  DACScale = input_data;
}

void Flauta :: set_impulse_scale(StkFloat scale)
{
  my_Excitation->set_impulse_scale(scale);
}

void Flauta :: set_cavity_length(StkFloat input_data)
{
  my_Resonator->set_cavity_length(input_data);
}

void Flauta :: set_chimney_length(StkFloat input_data)
{
  my_Resonator->set_chimney_length(input_data);
}

void Flauta :: set_radiation_flag(bool flag)
{
  my_Resonator->set_radiation_flag(flag);
}

void Flauta::set_visco_thermic_flag(bool flag)
{
  my_Resonator->set_visco_thermic_flag(flag);
}

void Flauta::setAttackTime(StkFloat time)
{
  my_Excitation->setAttackTime(time);
}

void Flauta::setReleaseTime(StkFloat time)
{
  my_Excitation->setReleaseTime(time);
}

StkFloat Flauta::computeSample(void)
{
  return(this->tick());
}


void Flauta :: controlChange(int input_label, 
			     StkFloat input_data)
{
 
  /*------------------------------*
   *     Control parameters       *
   *------------------------------*
   */
  StkFloat new_driving_pressure;

  if (input_label == 10){ // Blow Pressure Coarse
    coarse_pressure = (StkFloat)(input_data*2);
    new_driving_pressure = (StkFloat)(coarse_pressure + fine_pressure);
    if(new_driving_pressure < 0.0)
      new_driving_pressure = 0.0;
    my_Excitation->setPressure(new_driving_pressure); 
    cout << "Pressure = "<< new_driving_pressure << endl;
  }   
  

  else if (input_label == 11){ // Blow Pressure Fine
    fine_pressure = (StkFloat)(input_data*0.1);
    new_driving_pressure = coarse_pressure + fine_pressure;  
    if(new_driving_pressure < 0.0)
      new_driving_pressure = 0.0;
    my_Excitation->setPressure(new_driving_pressure); 
   cout << "Pressure = "<<new_driving_pressure << endl;
  }

  
  else if (input_label == 12){ // Pitch
    StkFloat curr_frequency = Midi2Pitch[(unsigned int)input_data];
    this->setFrequency(curr_frequency);
    cout << "Note is = " << curr_frequency << endl;
  }


  else if (input_label == 13){ // Vortex Amplitude 1
        my_Excitation->set_vortex_ampli_1((StkFloat)(input_data*0.1));
    //this->set_vortex_ampli_1((StkFloat)(input_data*0.1));
    cout << "Vortex Amplitude 1 is = " << (StkFloat)(input_data*0.1) << endl;
  }


  else if (input_label == 14){ // Vortex Amplitude 2
    my_Excitation->set_vortex_ampli_2((StkFloat)(input_data*0.1));
    cout << "Vortex Amplitude 2 is = " << (StkFloat)(input_data*0.1) << endl;
  }


  else if (input_label == 15){ // Turbulence Coefficient
    my_Excitation->set_turbulence_gain((StkFloat)(input_data*50));
    cout << "Turbulence Coefficient is = " << (StkFloat)(input_data*50) << endl;
  }


  else if (input_label == 16){ // Canal Length
    my_Excitation->set_channel_length((StkFloat)((input_data+5)*0.001));
    cout << "Canal Length is = " << (StkFloat)((input_data+5)*0.001) << endl;
  }


  else if (input_label == 17){ // Delta d
    my_Excitation->set_delta_d((StkFloat)(input_data*0.0001));
    cout << "Delta d is = " << (StkFloat)(input_data*0.0001) << endl;
  }


  else if (input_label == 18){ // Jet Width
    my_Excitation->set_jet_width((StkFloat)(input_data*0.001));
    cout << "Jet Width is = " << (StkFloat)(input_data*0.001) << endl;
  }


  else if (input_label == 19){ // Jet Amplitude cst
    //    jet_ampli_cst = (StkFloat)(input_data*0.1);
    //    my_Jet->set_Receptivity_FilterGain((StkFloat)(input_data*0.1));
    cout << "Jet Amplitude cst is = " << (StkFloat)(input_data*0.1) << endl;
  }


  else if (input_label == 20){ // Canal Height
    my_Excitation->set_jet_height((StkFloat)(input_data*0.00001));
    cout << "Canal Height is = " << (StkFloat)(input_data*0.00001) << endl;
  }


  else if (input_label == 21){ // Labium Position
    my_Excitation->set_labium_position((StkFloat)(input_data*0.00001));
    cout << "Labium Position is = " << (StkFloat)(input_data*0.00001) << endl;
  }


  else if (input_label == 22){ // Flue labium Distance
    //    flue_labium_dist = (StkFloat)(input_data*0.0001);
    //    cst_jet_filter = flue_labium_dist/(convection_factor*sampling_period);
    my_Excitation->set_flue_labium_dist((StkFloat)(input_data*0.0001));
    cout << "Flue Labium Distance is = " << (StkFloat)(input_data*0.0001) << endl;
  }


  else if (input_label == 23){ // Vibrato Gain
    my_Excitation->set_vibrato_gain( input_data * ONE_OVER_128 * 2 );
    cout << "Vibrato Gain is = " << input_data * ONE_OVER_128 * 2 << endl;
  
  }


  else if (input_label == 24){ // Vibrato Frequency
    my_Excitation->set_vibrato_frequency(input_data * ONE_OVER_128 * 12.0);
    cout << "Vibrato Frequency is = " << input_data * ONE_OVER_128 * 12.0<< endl;
  }

    
  else if (input_label == 30){ // Enable Radiation Filter
   //ACTUALIZAR!!!        Radiation_flag = (int)input_data;
  //ACTUALIZAR!!!     cout << "Radiation flag is = " << Radiation_flag << endl;
  }


  else if (input_label == 31){ // FrequencyMode/Square Jet 
   //ACTUALIZAR!!!        FrequencyMode_flag = (int)input_data;
   //ACTUALIZAR!!!        if(FrequencyMode_flag == 0)
   //ACTUALIZAR!!!          fine_pressure = 0;
   //ACTUALIZAR!!!    cout << "FrequencyMode flag is = " << FrequencyMode_flag << endl;
  }


  else if (input_label == 32){ // Enable Visco Thermic filter 
   //ACTUALIZAR!!!        ViscoThermic_flag = (int)input_data;
  //ACTUALIZAR!!!     cout << "Visco Thermic flag is = " << ViscoThermic_flag << endl;
  }


  else if (input_label == 33){ // Enable Sharp/Smooth Attacks 
    //ACTUALIZAR!!!       Attack_flag = (int)input_data;
    //ACTUALIZAR!!!        if(Attack_flag) 
    //ACTUALIZAR!!!         envelope->setAttackTime((StkFloat) 0.005);
    //ACTUALIZAR!!!       else
    //ACTUALIZAR!!!         envelope->setAttackTime((StkFloat) 0.3);
    
    //ACTUALIZAR!!!     cout << "Attack flag is = " << Attack_flag << endl;
  }


  else if (input_label == 40){ // Change output gain 
    DACScale = input_data*0.00005;
    cout << "DACSCALE = " << DACScale << endl;
  }

  else if (input_label == 50){ // Change cavity length
    //10-35 mm
    StkFloat curr_length = 0.010 + input_data*2/10000;
    my_Resonator->set_cavity_length(curr_length);
    cout << "Cavity length = " << curr_length << endl;
  }

  else if (input_label == 51){ // Change chimney length
    //5-30 mm
    StkFloat curr_length = 0.005 + input_data*2/10000;
    my_Resonator->set_chimney_length(curr_length);
    cout << "Chimney length = " << curr_length << endl;
  }


  else{
    fprintf(stderr, "bad input data in Control Change function  \n");
    exit(-1);    
  }
  

}
