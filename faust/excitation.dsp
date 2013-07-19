/*
 *  Copyright (C) 2011 Timo WestkÃÂ¤mper, Carlos BarrÃÂ­a, Daniel Tirado and Patricio de la Cuadra
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

// excitation
import("music.lib");
import("filter.lib");

// flauta libs
import("params.dsp");
import("constants.dsp");
//import("utils.dsp");

// out : sources, impulse
excitation(Vac, Pp) = (Vac,Pp) <: (_,_,_,!)
    : (_,(blow : (limit, limit, _)),_)
    : ((jet,_,_)
    <: (_,_,!,_,!,!,_,!)
    : (sources, _)) ~ _
    : (!,_,_);

limit = max(min_jet_vel) : min(max_jet_vel);

// adsr envelope 
// works more like the STK version
// in: a,d,s,r = attack (sec), decay (sec), sustain (percentage), release (sec)
//     t       = trigger signal
adsr2(a,d,s,r,t) = env ~ (_,_) : (!,_) // the 2 'state' signals are fed back
with {
    env (p2,y) =
        (t>0) & (p2|(y>=1)),                    // p2 = decay-sustain phase
        (y + p1*u - (p2&(y>s))*v*y - p3*w*y)    // y  = envelop signal
        *((p3==0)|(y>=eps))                     // cut off tails to prevent denormals
    with {
    	p1 = (p2==0) & (t>0) & (y<1);           // p1 = attack phase
    	p3 = (t<=0) & (y>0);                    // p3 = release phase
    	// samples in attack, decay and release
        samples(x) = SR * x + (x==0);
        na = samples(a); nd = samples(d); nr = samples(r);
    	// correct zero sustain level
    	z = s + (s==0.0)*db2linear(-60);
    	// attack, decay and (-60dB) release rates
    	u = 1 / na; v = 1 / nd; w = z / nr;
    	// values below this threshold are considered zero in the release phase
    	eps = db2linear(-120);
    };
};


// blow
// in : mouth pressure
// out : uj, uj_steady, impulse


//blow2 = (((pressure * envelope) <: (_ + vibrato * _) : max(0)),_ ) 
//    : bernoulli : (max(0), max(0), _)
//with {
//    envelope = gate : adsr2(env_attack, env_decay, env_sustain, env_release);
//    vibrato = vibrato_gain * osc(vibrato_freq);
//};

blow = (pressure,_ ) : (max(0),_) : bernoulli : (max(0), max(0), _) ;



// bernoulli
// out : bernoulli, uj_steady, impulse
bernoulli(pin, pout) = (pin,pout) <: ((curr_velocity ~ _), ((curr_velocity_steady ~ _), !)) 
    // in : cv, cvp, cvs
    <: (_,!,_,impulse(_, _),!)
with {
    curr_velocity(prev) = prev + (const_bernoulli * ((_- _) - (HALF_DENSITY * (prev * prev)))), prev;

    curr_velocity_steady(prev) = prev + (const_bernoulli * (_ - (HALF_DENSITY * (prev * prev)))); 

    // in : cv, cvp
    impulse = const_impulse * (_-_) : max(0) : min(max_impulse);

    const_impulse = impulse_scale * (SR * AIR_DENSITY * 0.61 * chim_radius);

    max_impulse = 500;
    
    chan_len = channel_length : max(0.001);
    const_bernoulli = 1 / (SR * AIR_DENSITY * chan_len);
};

// out : eta_d, Uj_d
jet(hyd_feed, Vac, Uj, Uj_steady) = (hyd_feed,Vac,Uj_steady,Uj) : (receptivity,_) : (jetDelay, jetDelay)
with {
    // initial definition of delay length
    initial_delay_length = floor((max_flue_labium_d / (min_convection_f * min_jet_vel)) / sampling_period);
    
    delay_length = (jet_msamples_per_sec / Uj_steady) : max(0.5) : min(initial_delay_length);

    jet_msamples_per_sec = flue_labium_distance / (convection_f * sampling_period);
          
    jetDelay = fdelay(MAX_DELAY_LENGTH, delay_length);
    
    sampling_period = 1.0 / SR;
};

receptivity = recept~ _ : (!,_);

recept(last_Uj,hyd_feed, vac, Uj_steady) = (u,(excitation : jet_filter_peak1 : jet_filter_peak2 : jet_filter_shelf : _ *1e-4))
with {
    excitation = TWO_div_M_PI * vac + hyd_feed;

    diff = abs(Uj_steady - last_Uj);
    u = select2(diff > step_Uj, last_Uj, Uj_steady);

    jet_filter_peak1 = receptivity_peak_filter(
        0.0645*(u/jet_height)*(2.0/(2.0*M_PI*SR)),
        0.3278*(u/jet_height)*(2.0/(2.0*M_PI*SR)),
        pow(10, 2.6337*(flue_labium_distance / jet_height)/20.0));

    jet_filter_peak2 = receptivity_peak_filter(
        0.3278*(u/jet_height)*(2.0/(2.0*M_PI*SR)),
        1.2006*(u/jet_height)*(2.0/(2.0*M_PI*SR)),
        pow(10, 5.0719*(flue_labium_distance / jet_height)/20.0));

    jet_filter_shelf = receptivity_shelf_filter(
        0.2954*(u/jet_height)*(2.0/(2.0*M_PI*SR)),
        pow(10.0, 2.3884*(flue_labium_distance / jet_height)/20.0),
        pow(10.0, 0.0*(flue_labium_distance / jet_height)/20.0));

};

receptivity_shelf_filter(transition_freq, low_gain, high_gain) = iir((b0,b1),(a1))
with {
    transition_gain = sqrt(low_gain * high_gain);
    pi_transition_frequency = M_PI * transition_freq;
    zero = (high_gain * high_gain) + (low_gain * low_gain) - 2.0* (transition_gain * transition_gain);
    alpha = select2(zero != 0, 0, lambda - (lambda / fabs(lambda)) * sqrt((lambda * lambda) - 1.0));
    lambda = ((high_gain * high_gain) - (low_gain * low_gain)) / zero;

    beta0 = 0.5 * ((low_gain + high_gain) + (low_gain - high_gain) * alpha);
    beta1 = 0.5 * ((low_gain - high_gain) + (low_gain + high_gain) * alpha);
    rho = sin(pi_transition_frequency/2.0 - M_PI/4.0) / sin(pi_transition_frequency/2.0 + M_PI/4.0);

    b0 = (beta0 + rho*beta1) / (1.0 + rho*alpha);
    b1 = (beta1 + rho*beta0) / (1.0 + rho*alpha);
    a1 = (rho + alpha) / (1.0 + rho*alpha);     
};

receptivity_peak_filter(low_freq, high_freq, gain) = iir((b0,b1,b2),(a1,a2))
with {
    c1 = cos(M_PI * low_freq);
    c2 = cos(M_PI * high_freq);
    beta = (1.0 + c1*c2) / (c1+c2);
    wc = acos(beta - (beta/fabs(beta)) * sqrt((beta*beta)-1.0)); 
    cc = cos(wc);
    sc = sin(wc);

    Q = sqrt(gain * sc*sc * (c1+c2) / (4.0 * (2.0*cc - c1 - c2)));
    k = (2.0*Q - sc) / (2.0*Q + sc);

    b0 = ((1.0+k) + gain*(1.0-k))/2.0;
    b1 = (0.0-cc)*(1+k);
    b2 = ((1.0+k) - gain*(1.0-k))/2.0;
    a1 = (0.0-cc)*(1+k);
    a2 = k;
    
};

// out : hyd_feedback, sources
sources(eta_d, Uj_d, Vac) = (eta_d,Uj_d,Vac) <: (_,_,!,!,_,_) : (jetDrive, turbulence, vortex) : (_,_+_+_);

// vortex
vortex(vac) = select2(vac > 0, -va2, va1) * VORTEX_CTE * vac * vac
with {
    va1 = vortex_ampli1;
    va2 = vortex_ampli2;
};

// XXX tanh lookup table behaves a little bit different than in STK version
tanh_fast = min(4.0) : max(-4.0) : (1000*(_+4.0)) <: (int(_),decimal(_)) : lookup
with {
   size = 8000;
   index = (+(1)~_ ) - 1; // 0,1,2,...
   tanh_creation = float(index) / size * 8.0 -4.0 : tanh;
   table(x) = rdtable(size+1, tanh_creation, int(x)); // 0.0-8.0

   tanh    = ffunction(float tanh (float), <math.h>,"");

   // linear interpolation
   decimal(x) = x - int(x);
   lookup(x, frac) = select2(frac > 0, table(x), ((table(x), table(x+1)) <: (_,_,_,!) : (_+frac*(_-_)) ));
};

// jetDrive
// in : jet_displacement, uj
// out : hyd_feed, jet_drive
jetDrive(jet_displacement, uj) = (jet_displacement, uj) : Qin <: hyd_constant * _, (jet_drive_cst * (_ - _'))
with {

    Qin(jet_displacement, uj) = uj * b * jet_width * (1.0 + tanh(tanh_argument))
    with {
      jet_hgt = jet_height : max(0.0001); 
      b_constant = jet_shape : max(0.1) : min(2.9); 
      b = b_constant * jet_hgt;
      tanh_argument = (jet_displacement - labium_position) / b;
    };

    jet_wdt = jet_width : max(0.001);
    fl_dist = flue_labium_distance : max(0.001);

    hyd_constant = 2.0 * ratio * (kappa * kappa - 1.0) / (M_PI * (kappa * kappa + 1.0))
    with {
        ratio = delta_d / fl_dist;
        beta = ratio + sqrt(ratio * (2.0 + ratio));
        kappa = 1.0 + beta;
    };

    jet_drive_cst = (-1.0 * AIR_DENSITY * delta_d) / (jet_wdt * fl_dist * sampling_period);
  
    sampling_period = 1.0 / SR;

};


// turbulence
turbulence(uj) = turbulence_gain * MAX_AMPLITUDE * uj * uj * jet_height * filtered_noise
with {

   // turbulence_gain * MAX_AMPLITUDE * Uj * Uj * h * noise_filter->tick(random_sample);

//   filtered_noise = noise : iir((b1,b2,b3),(a1,a2));
   filtered_noise = 1 : iir((b1,b2,b3),(a1,a2));
   
   a1 = -1.59164698202301;
   a2 = 0.69491246133220;
   b1 = 0.15254376933390;
   b2 = 0.0;
   b3 = -0.15254376933390;
};

//process = excitation;
