#include "Receptivity.h"
#include <iostream>
using namespace std;

Receptivity::Receptivity(StkFloat  _jet_height,
			 StkFloat  _flue_labium_dist
			 ):jet_height(_jet_height),
			 flue_labium_dist(_flue_labium_dist)
{
  sampling_frequency =  Stk::sampleRate();
 
  StkFloat long_Coeffs[3] = {1,0,0};
  StkFloat short_Coeffs[2] = {1,0};

  //  std::vector<double> long_vector(long_Coeffs, long_Coeffs + 3);
  //  std::vector<double> short_vector(short_Coeffs, short_Coeffs + 2);
  //  Jet_filter_peak1 = new MyFilter(long_vector,long_vector);
  //  Jet_filter_peak2 = new MyFilter(long_vector,long_vector);
  //  Jet_filter_shelf = new MyFilter(short_vector,short_vector);
  Jet_filter_peak1 = new MyFilter(3, long_Coeffs,3, long_Coeffs);
  Jet_filter_peak2 = new MyFilter(3, long_Coeffs,3, long_Coeffs);
  Jet_filter_shelf = new MyFilter(2, short_Coeffs,2, short_Coeffs);
  
  //  Jet_filter_peak1_inv = new MyFilter(long_vector,long_vector);
  //  Jet_filter_peak2_inv = new MyFilter(long_vector,long_vector);
  //  Jet_filter_shelf_inv = new MyFilter(short_vector,short_vector);
  Jet_filter_peak1_inv = new MyFilter(3, long_Coeffs,3, long_Coeffs);
  Jet_filter_peak2_inv = new MyFilter(3, long_Coeffs,3, long_Coeffs);
  Jet_filter_shelf_inv = new MyFilter(2, short_Coeffs,2, short_Coeffs);
  
  StkFloat one_over_B_Coeffs[3] = {0.00001975, -0.00001606, -0.00000268};
  StkFloat one_over_A_Coeffs[3] = {1.0000, -1.9488, 0.94901};
  //  std::vector<double> one_over_omega_B_vector(one_over_B_Coeffs, one_over_B_Coeffs + 3);
  //  std::vector<double> one_over_omega_A_vector(one_over_A_Coeffs, one_over_A_Coeffs + 3);
  //  Jet_fiter_one_over_omega = new MyFilter(one_over_omega_B_vector, one_over_omega_A_vector);
  Jet_fiter_one_over_omega = new MyFilter(3, one_over_B_Coeffs,3,  one_over_A_Coeffs);

  //DEBUGGING...
  //  set_Coefficients(15.0);
}


Receptivity::~Receptivity(){   
  
  delete Jet_filter_peak1;
  delete Jet_filter_peak2;
  delete Jet_filter_shelf;
  delete Jet_filter_peak1_inv;
  delete Jet_filter_peak2_inv;
  delete Jet_filter_shelf_inv;
  delete Jet_fiter_one_over_omega;

}

void Receptivity::clear(){
   Jet_filter_peak1->clear();
   Jet_filter_peak2->clear();
   Jet_filter_shelf->clear();
   Jet_filter_peak1_inv->clear();
   Jet_filter_peak2_inv->clear();
   Jet_filter_shelf_inv->clear();
   Jet_fiter_one_over_omega->clear();
}  


void Receptivity::calculate_peak_filter(StkFloat low_freq,
					StkFloat high_freq,
					StkFloat gain,
					StkFloat *B_coeffs,
					StkFloat *A_coeffs
					/*std::vector<StkFloat> &B_coeffs,
					  std::vector<StkFloat> &A_coeffs*/){
  if(low_freq >= high_freq){
    cout<<"Receptivity: ERROR- low frequency must be strictly lower than high frequency"<< endl;
    return;
  }
  else if((low_freq == 0.0) | (high_freq == 1.0)){
    cout<<"Receptivity: ERROR- transition must be away from band edges"<< endl;
    return;
  } 
  else if(gain < 0){
    cout<<"Receptivity: ERROR- input gain must be possitive"<< endl;
    return;
  } 
  //  else if(B_coeffs.size() != 3 | A_coeffs.size() != 3){
  //    cout<<"Receptivity: ERROR- vector size must be three for both numerator and denominator"<< endl;
  //    return;
  //  } 
  
  StkFloat  c1 = cos(PI * low_freq);
  StkFloat  c2 = cos(PI * high_freq);
  StkFloat  beta = (1 + c1*c2)/(c1 + c2);
  StkFloat  wc = acos(beta - (beta/fabs(beta))*sqrt((beta*beta)-1));//sign(x) = x/abs(x)
  StkFloat  cc = cos(wc);
  StkFloat  sc = sin(wc);
  
  StkFloat  Q = sqrt(gain * sc*sc * (c1 + c2) / (4 * (2*cc - c1 - c2)));
  StkFloat  k = (2*Q - sc) / (2*Q + sc);

  B_coeffs[0] = ((1+k) + gain*(1-k))/2;
  B_coeffs[1] = -cc*(1+k);
  B_coeffs[2] = ((1+k) - gain*(1-k))/2;
  A_coeffs[0] = 1;
  A_coeffs[1] = -cc*(1+k);
  A_coeffs[2] = k;

  //  B_coeffs.at(0) = ((1+k) + gain*(1-k))/2;
  //  B_coeffs.at(1) = -cc*(1+k);
  //  B_coeffs.at(2) = ((1+k) - gain*(1-k))/2;
  //  A_coeffs.at(0) = 1;
  //  A_coeffs.at(1) = -cc*(1+k);
  //  A_coeffs.at(2) = k;

  //DEBUGGING
//   std::vector<double>::const_iterator p1;
//   for(p1 =  B_coeffs.begin(); p1 != B_coeffs.end();p1++)
//     cout << *p1 << ' ';
//   cout << endl;
//   std::vector<double>::const_iterator p2;
//   for(p2 =  A_coeffs.begin(); p2 != A_coeffs.end();p2++)
//     cout << *p2 << ' ';
//   cout << endl;
}


void Receptivity::calculate_shelf_filter(StkFloat transition_freq,
					 StkFloat low_gain,
					 StkFloat high_gain,
					 StkFloat *B_coeffs,
					 StkFloat *A_coeffs
					 /*std::vector<StkFloat> &B_coeffs,
					   std::vector<StkFloat> &A_coeffs*/){
  if((low_gain < 0) | (high_gain < 0)){
    cout<<"Receptivity shelf: ERROR- input gains must be possitive"<< endl;
    return;
  } 
  if((transition_freq > 1) | (transition_freq < 0)){
    cout<<"Receptivity shelf: ERROR- transition frequency must be between 0 and 1"<< endl;
    return;
  }
  //  else if(B_coeffs.size() != 2 | A_coeffs.size() != 2){
  //    cout<<"Receptivity shelf: ERROR- vector size must be 2 for both numerator and denominator"<< endl;
  //    return;
  //  } 
  
  StkFloat transition_gain = sqrt(low_gain * high_gain);

  StkFloat pi_transition_frequency = PI * transition_freq;

  StkFloat Zero = (high_gain*high_gain) + (low_gain*low_gain) - 2*(transition_gain*transition_gain);
  StkFloat alpha;
  
  if (Zero == 0){
      // one-zero cannonical system
    alpha = 0;
  }
  else{
    // pole needed
    StkFloat lambda = ((high_gain*high_gain) - (low_gain*low_gain)) / Zero;
    alpha = lambda - (lambda/fabs(lambda))*sqrt((lambda*lambda) - 1);
    //sign(lambda) = lambda/fabs(lambda)
  }
  
  StkFloat beta0 = 0.5 * ((low_gain + high_gain) + (low_gain - high_gain) * alpha);
  StkFloat beta1 = 0.5 * ((low_gain - high_gain) + (low_gain + high_gain) * alpha);

  StkFloat rho = sin(pi_transition_frequency/2 - PI/4) / sin(pi_transition_frequency/2 + PI/4);

  B_coeffs[0] = (beta0 + rho*beta1) / (1 + rho*alpha);
  B_coeffs[1] = (beta1 + rho*beta0) / (1 + rho*alpha);
  A_coeffs[0] = 1;
  A_coeffs[1] = (rho + alpha)/(1 + rho*alpha);
  //  B_coeffs.at(0) = (beta0 + rho*beta1) / (1 + rho*alpha);
  //  B_coeffs.at(1) = (beta1 + rho*beta0) / (1 + rho*alpha);
  //  A_coeffs.at(0) = 1;
  //  A_coeffs.at(1) = (rho + alpha)/(1 + rho*alpha);

  //DEBUGGING
//   std::vector<double>::const_iterator p1;
//   for(p1 =  B_coeffs.begin(); p1 != B_coeffs.end();p1++)
//     cout << *p1 << ' ';
//   cout << endl;
//   std::vector<double>::const_iterator p2;
//   for(p2 =  A_coeffs.begin(); p2 != A_coeffs.end();p2++)
//     cout << *p2 << ' ';
//   cout << endl;

}

StkFloat Receptivity::tick(StkFloat Vac, StkFloat Hyd_feedback)
{
  
  /******************************************************
   *    Filtering the acoustic velocity. The transverse *
   *    acoustic velocity is the input of the filter.   *
   *	Perturbation at the flue exit. It consists	* 		
   *	of a contribution from the acoustic field	*
   *	in the pipe and one from the direct 		*
   *	hydrodynamic feedback due to the jet-labium	*
   *	interaction.					*
   ******************************************************/
 
  excitation = TWO_div_M_PI * Vac + Hyd_feedback;
  
  //  StkFloat lastOut =(0.5*Jet_filter_shelf->tick(Jet_filter_peak2->tick(Jet_filter_peak1->tick(excitation))) +
  //   0.5*Jet_filter_shelf_inv->tick(Jet_filter_peak2_inv->tick(Jet_filter_peak1_inv->tick(excitation)))) - 
  //  excitation ;

 
  // lastOut = Jet_fiter_one_over_omega->tick(Jet_filter_shelf->tick(Jet_filter_peak2->tick(Jet_filter_peak1->tick(excitation))));
  lastOut = 1e-4*Jet_filter_shelf->tick(Jet_filter_peak2->tick(Jet_filter_peak1->tick(excitation)));
    return(lastOut);  
}


  
void Receptivity::set_Coefficients(StkFloat Uj_steady)

{


  //  StkFloat empty_2[2] =  {1.0, 0.0};
  //  StkFloat empty_3[3] =  {1.0, 0.0, 0.0};

  //  std::vector<StkFloat> B_shelf_coeffs(empty_2,empty_2+2);
  //  std::vector<StkFloat> A_shelf_coeffs(empty_2,empty_2+2);
  StkFloat B_shelf_coeffs[2];
  StkFloat A_shelf_coeffs[2];
  
  //  std::vector<StkFloat> B_peak1_coeffs(empty_3,empty_3+3);
  //  std::vector<StkFloat> A_peak1_coeffs(empty_3,empty_3+3);
  StkFloat B_peak1_coeffs[3];
  StkFloat A_peak1_coeffs[3];
  
  //  std::vector<StkFloat> B_peak2_coeffs(empty_3,empty_3+3);
  //  std::vector<StkFloat> A_peak2_coeffs(empty_3,empty_3+3);
  StkFloat B_peak2_coeffs[3];
  StkFloat A_peak2_coeffs[3];
  
  this->calculate_shelf_filter(0.2954*(Uj_steady/jet_height)*(2/(2*PI*sampling_frequency)), 
			       pow(10,2.3884*(flue_labium_dist/jet_height)/20),
			       pow(10,0.0*(flue_labium_dist/jet_height)/20),
			       B_shelf_coeffs,
			       A_shelf_coeffs);
  
  Jet_filter_shelf->setCoefficients(2, B_shelf_coeffs,2, A_shelf_coeffs);
  
  Jet_filter_shelf_inv->setCoefficients(2, A_shelf_coeffs,2,  B_shelf_coeffs);
  
  
  
  //////////////////////////////////
  
  this->calculate_peak_filter(0.0645*(Uj_steady/jet_height)*(2/(2*PI*sampling_frequency)), 
			      0.3278*(Uj_steady/jet_height)*(2/(2*PI*sampling_frequency)),
			      pow(10,2.6337*(flue_labium_dist/jet_height)/20),
			      B_peak1_coeffs,
			      A_peak1_coeffs);
  
  Jet_filter_peak1->setCoefficients(3, B_peak1_coeffs,3, A_peak1_coeffs);
  
  Jet_filter_peak1_inv->setCoefficients(3, A_peak1_coeffs,3,  B_peak1_coeffs);
  
  ///////////////////////////////////
  
  this->calculate_peak_filter(0.3278*(Uj_steady/jet_height)*(2/(2*PI*sampling_frequency)), 
			      1.2006*(Uj_steady/jet_height)*(2/(2*PI*sampling_frequency)),
			      pow(10,5.0719*(flue_labium_dist/jet_height)/20),
			      B_peak2_coeffs,
			      A_peak2_coeffs);
  

  Jet_filter_peak2->setCoefficients(3, B_peak2_coeffs,3, A_peak2_coeffs);
  Jet_filter_peak2_inv->setCoefficients(3, A_peak2_coeffs,3,  B_peak2_coeffs);
  

}


void Receptivity::set_FilterGain(StkFloat )
{
  //Jet_filter_filter->setGain(gain);//I don't think its a good idea to change this gain!
}


StkFloat Receptivity::get_minUj()
{
  return(min_Uj);
}
StkFloat Receptivity::get_maxUj()
{
  return(max_Uj);
}

StkFloat Receptivity::get_stepUj()
{
  return(step_Uj);
}

void Receptivity::noteOff()
{
  //  clear();
}
