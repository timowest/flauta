#include "Resonator.h"


Resonator::Resonator(StkFloat cav_length,
		     StkFloat cav_radius,
		     StkFloat chim_length,
		     StkFloat chim_radius,
		     StkFloat end_length,
		     StkFloat end_radius,
		     StkFloat tub_length,
		     StkFloat tub_radius)
{
  /*------------------------------*
   *     Geometric parameters     *
   *------------------------------*
   */
  sampling_frequency =  Stk::sampleRate();
  sampling_period = 1.0/sampling_frequency;

  //Embouchure Cavity 
  cavity_length = cav_length;
  cavity_radius = cav_radius;
  cavity_samples = cavity_length*sampling_frequency/TWO_SOUND_SPEED;
  
  //Embouchure Chimney
  chimney_length = chim_length;
  chimney_radius = chim_radius;
  chimney_samples = chimney_length*sampling_frequency/TWO_SOUND_SPEED;
  
  //Embouchure end correction
  end_corr_length = end_length;
  end_corr_radius = end_radius;
  end_corr_samples = end_corr_length*sampling_frequency/TWO_SOUND_SPEED;

  //Tube
  tube_length = tub_length;
  tube_radius = tub_radius;
  tube_samples = tube_length*sampling_frequency/TWO_SOUND_SPEED;
  
  //Junction
  junction_gain = -(chimney_radius*chimney_radius)/((chimney_radius*chimney_radius) + 2*(cavity_radius*cavity_radius));

  //filter flags
  radiation_flag = 1;
  visco_thermic_flag = 1;

  /*------------------------------*
   *     STK objects              *
   *------------------------------*
   */
  
  tubeDelayRight = new DelayL( tube_samples, MAX_DELAY_LENGTH );    
  tubeDelayLeft = new DelayL( tube_samples, MAX_DELAY_LENGTH );
  chimneyDelayRight = new DelayL( chimney_samples, MAX_DELAY_LENGTH );    
  chimneyDelayLeft = new DelayL( chimney_samples, MAX_DELAY_LENGTH );
  cavityDelayRight = new DelayL( cavity_samples, MAX_DELAY_LENGTH );    
  cavityDelayLeft = new DelayL( cavity_samples, MAX_DELAY_LENGTH );
  endDelay = new DelayL( end_corr_samples, MAX_DELAY_LENGTH);
 
  
  /*
   *--------------------------------------------*
   *	Filter coefficients for the radiation	*
   *--------------------------------------------*
   */

  StkFloat a1_rad, a2_rad, a3_rad, b1_rad, b2_rad, b3_rad;

  a1_rad = 1.0000;
  a2_rad = -0.3587; 
  a3_rad = -0.0918;
  b1_rad = -0.1254;
  b2_rad = -0.3237;
  b3_rad = -0.1003;

  StkFloat A_rad_Coeffs[RAD_ORDER]= {a1_rad, a2_rad, a3_rad};
  StkFloat B_rad_Coeffs[RAD_ORDER]= {b1_rad, b2_rad, b3_rad};
  //std::vector<double> A_rad_vector(A_rad_Coeffs, A_rad_Coeffs + 3);
  //std::vector<double> B_rad_vector(B_rad_Coeffs, B_rad_Coeffs + 3);

    radiation_filter = new MyFilter (RAD_ORDER, B_rad_Coeffs, RAD_ORDER, A_rad_Coeffs);
  //radiation_filter = new MyFilter (B_rad_vector, A_rad_vector);
    mouth_radiation_filter = new MyFilter (RAD_ORDER, B_rad_Coeffs, RAD_ORDER, A_rad_Coeffs);
    //mouth_radiation_filter = new MyFilter (B_rad_vector, A_rad_vector);

  /*
   *------------------------------------*
   *	Filter coefficients for		*	 
   *	the visco-thermal losses.	*
   *------------------------------------*
   */ 

  StkFloat a1_vt, a2_vt, a3_vt, a4_vt, b1_vt, b2_vt, b3_vt, b4_vt;
  // recorder parameters
  a1_vt = 1.0;
  a2_vt = -0.33623476246554;
  a3_vt = -0.71257915055968;
  a4_vt = 0.14508304017256;
  b1_vt = 0.83820223947141;
  b2_vt = -0.16888603248373;
  b3_vt = -0.64759781930259;
  b4_vt =  0.07424498608506;
  
  StkFloat B_vt_Coeffs[VT_ORDER]= {b1_vt, b2_vt, b3_vt, b4_vt};
  StkFloat A_vt_Coeffs[VT_ORDER]= {a1_vt, a2_vt, a3_vt, a4_vt};
  //  std::vector<double> A_vt_vector(A_vt_Coeffs, A_vt_Coeffs + 4);
  //  std::vector<double> B_vt_vector(B_vt_Coeffs, B_vt_Coeffs + 4);
  
  //  visco_thermic_filter = new MyFilter(B_vt_vector, A_vt_vector);
  visco_thermic_filter = new MyFilter(VT_ORDER, B_vt_Coeffs, VT_ORDER, A_vt_Coeffs);

 


}

Resonator::~Resonator(){  
  delete chimneyDelayRight;  
  delete chimneyDelayLeft;
  delete cavityDelayRight;  
  delete cavityDelayLeft;
  delete tubeDelayRight;  
  delete tubeDelayLeft;
  delete endDelay;

  delete visco_thermic_filter;
  delete radiation_filter;
  delete mouth_radiation_filter;

}


StkFloat Resonator::tick(StkFloat current_sources, StkFloat impulse)
{

  // Propagate to the tube throught the 3 port junction
  
  StkFloat temp,temp2,temp3,temp4,temp5,temp6;

  temp = chimneyDelayRight->tick(current_sources +(impulse/2) + endDelay->lastOut());
  // the common sigma
  temp2 = junction_gain* (-2*temp + cavityDelayRight->lastOut() + tubeDelayLeft->lastOut());
  
  // The cavity
  temp3 = cavityDelayLeft->tick(temp2 + tubeDelayLeft->lastOut());
  cavityDelayRight->tick(temp3);
  
  // The chimney
  temp4 = chimneyDelayLeft->tick(temp2 + cavityDelayRight->lastOut() + tubeDelayLeft->lastOut() - temp);
  endDelay->tick(mouth_radiation_filter->tick(temp4 + impulse/2));
  // The tube
  temp5 = visco_thermic_tick(tubeDelayRight->tick(temp2 + cavityDelayRight->lastOut()));
  temp6 = radiation_tick(temp5);
  tubeDelayLeft->tick(temp6);

  // OUTPUT:
  //Reading at the embochure
  //  last_Output = endDelay->lastOut() + chimneyDelayLeft->lastOut();
  
  // Reading at the end of the tube
  last_Output = temp5 + temp6;
  return (last_Output);


}

StkFloat Resonator::radiation_tick(StkFloat in)
{
  if (radiation_flag)
    return(radiation_filter->tick(in));
  else
    // return(in);//we probably need to delay this to make it comparable with the other case
    // return(0.846*in);
    // return(radiation_filter->tick(-in));
    return(radiation_filter->tick(in));
}

StkFloat Resonator::visco_thermic_tick(StkFloat in)
{
  if (visco_thermic_flag)
    return(visco_thermic_filter->tick(in));
  else
    return(in);//we probably need to delay this to make it comparable with the other case
}

void Resonator::set_radiation_flag(bool flag)
{
  radiation_flag = flag;
}

void Resonator::set_visco_thermic_flag(bool flag)
{
  visco_thermic_flag = flag;
}

void Resonator::noteOn(StkFloat freq){
  this->setFrequency(freq);
}

void Resonator::noteOff(){
  //this->clear();
}

void Resonator::clear(){  
  chimneyDelayRight->clear();  
  chimneyDelayLeft->clear();
  cavityDelayRight->clear();  
  cavityDelayLeft->clear();
  tubeDelayRight->clear();  
  tubeDelayLeft->clear();
  endDelay->clear();
  
  visco_thermic_filter->clear();
  radiation_filter->clear();
  mouth_radiation_filter->clear();
}

StkFloat Resonator::get_mouth_acoustic_pressure()
{
  return(endDelay->lastOut() + chimneyDelayLeft->lastOut());
}

StkFloat Resonator::get_acoustic_velocity()
{
  return(ONE_OVER_RHO_C*(endDelay->lastOut() - chimneyDelayLeft->lastOut()));
}

StkFloat Resonator::get_impedance()
{
  return(AIR_DENSITY*0.61*chimney_radius/(2*sampling_period));
}

  
void Resonator::set_tube_delay(StkFloat delay)
{
  tubeDelayRight->setDelay(check_boundaries(delay));
  tubeDelayLeft->setDelay(check_boundaries(delay));  
}

void Resonator::set_cavity_delay(StkFloat delay)
{
  cavityDelayRight->setDelay(check_boundaries(delay));
  cavityDelayLeft->setDelay(check_boundaries(delay));  
}

void Resonator::set_cavity_length(StkFloat length)
{
  //receives the length in mts.
  // from mts to samples:
  StkFloat cavity_samples = length*sampling_frequency/TWO_SOUND_SPEED;
  set_cavity_delay(cavity_samples);
}

void Resonator::set_chimney_delay(StkFloat delay)
{
  chimneyDelayRight->setDelay(check_boundaries(delay));
  chimneyDelayLeft->setDelay(check_boundaries(delay));  
}

void Resonator::set_chimney_length(StkFloat length)
{
  //receives the length in mts.
  // from mts to samples:
  StkFloat chimney_samples = length*sampling_frequency/TWO_SOUND_SPEED;
  set_chimney_delay(chimney_samples);
}

void Resonator::set_end_delay(StkFloat delay)
{
  endDelay->setDelay(check_boundaries(delay));
}

void Resonator::set_end_length(StkFloat length)
{
  //receives the length in mts.
  // from mts to samples:
  StkFloat end_samples = length*sampling_frequency/TWO_SOUND_SPEED;
  set_end_delay(end_samples);
}

void Resonator::setFrequency(StkFloat freq)//freq in Hz
{
  
  // To get the right frequency
  // all compensations from the filters need to be added here
 
  StkFloat temp = sampling_frequency / (freq) - (StkFloat) RAD_ORDER - (StkFloat) VT_ORDER;    /* Length - approx. filter delay */

  this->set_tube_delay(temp);
}

StkFloat Resonator :: get_frequency()
{
  return (StkFloat)sampling_frequency/(tubeDelayRight->getDelay() + (StkFloat) RAD_ORDER + (StkFloat) VT_ORDER);
}

StkFloat Resonator :: check_boundaries(StkFloat value)
{
  if (value < 0.5){
    value = 0.5;
  }
  if (value > MAX_DELAY_LENGTH){
    value = MAX_DELAY_LENGTH;
  }
  return value;
}
