/*
 *  Copyright (C) 2011 Timo Westkämper, Carlos Barría, Daniel Tirado and Patricio de la Cuadra
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
excitation(Vac,Pp) = (Vac,Pp) <: (_,_,_,!)
    : (_,(blow : (limit, limit, (_/2))),_) 
    : ((jet,_,_)
    <: (_,_,!,_,!,!,_,!)
    : (sources, _)) ~ _
    : (!,_,_);

limit = max(min_jet_vel) : min(max_jet_vel);

// blow
// in : mouth pressure
// out : uj, uj_steady, impulse
blow = (((envelope * target_driving_pressure) <: (_ + (vibrato_gain * vibrato) * _) : max(0)),_ ) 
    : bernoulli : (max(0), max(0), _)
with {
    target_driving_pressure = pressure;

    //envelope = gate : adsr(0.005 * SR, 0.01, 100, 0.01);
    envelope = gate : adsr(env_attack * SR, env_decay, env_sustain, env_release);

    vibrato = vibrato_gain * osc(vibrato_freq) * vibrato_env; 
    vibrato_env = gate : adsr(vib_attack * SR, vib_decay, vib_sustain, vib_release);
};

// bernoulli
// out : bernoulli, uj_steady, impulse
bernoulli(pin,pout) = (pin,pout) <: ((curr_velocity ~ _), ((curr_velocity_steady ~ _), !)) 
    // in : cv, cvp, cvs
    <: (_,!,_,impulse(_, _),!)
with {
    curr_velocity(prev) = prev + (const_bernoulli * ((_- _) - (HALF_DENSITY * (prev * prev)))) : in_goe_out, prev;

    curr_velocity_steady(prev) = prev + (const_bernoulli * (_ - (HALF_DENSITY * (prev * prev)))) : in_goe_out; 

    // in : cv, cvp
    impulse = const_impulse * (_- _) : max(0) : min(max_impulse) : in_goe_out;

    in_goe_out(x) = select2(pin >= pout, 0.0, x);

    const_impulse = impulse_scale * (SR * AIR_DENSITY * 0.61 * chim_radius);

    max_impulse = 500;

    const_bernoulli = 1 / (SR * AIR_DENSITY * channel_length);
};

// out : eta_d, Uj_d
jet(hyd_feed,Vac,Uj_steady,Uj) = (hyd_feed,Vac,Uj_steady,Uj) : (receptivity,_) : (jetDelay, jetDelay)
with {
    
    // initial definition of delay length
    initial_delay_length = floor((max_flue_labium_d / (min_convection_f * min_jet_vel)) / SR);
         
    delay_length = (jet_msamples_per_sec / Uj_steady) : max(0.5) : min(initial_delay_length);

    jet_msamples_per_sec = flue_labium_distance / (convection_f * SR);

    jetDelay = fdelay(MAX_DELAY_LENGTH, delay_length);
};

receptivity(hyd_feed, vac, uj_steady) = excitation : jet_filter_peak1 : jet_filter_peak2 : jet_filter_shelf : *(1e-4)
with {
    excitation = TWO_div_M_PI * vac + hyd_feed;

    jet_filter_peak1 = receptivity_peak_filter(
        0.0645*(uj_steady/jet_height)*(2.0/(2.0*PI*SR)),
        0.3278*(uj_steady/jet_height)*(2.0/(2.0*PI*SR)),
        pow(10, 2.6337*(flue_labium_distance / jet_height)/20.0));

    jet_filter_peak2 = receptivity_peak_filter(
        0.3278*(uj_steady/jet_height)*(2.0/(2.0*PI*SR)),
        1.2006*(uj_steady/jet_height)*(2.0/(2.0*PI*SR)),
        pow(10, 5.0719*(flue_labium_distance / jet_height)/20.0));

    jet_filter_shelf = receptivity_shelf_filter(
        0.2954*(uj_steady/jet_height)*(2.0/(2.0*PI*SR)),
        pow(10.0, 2.3884*(flue_labium_distance / jet_height)/20.0),
        pow(10.0, 0.0*(flue_labium_distance / jet_height)/20.0));

    //jet_filter_one_over_omega = _; 
};

receptivity_shelf_filter(transition_freq, low_gain, high_gain) = iir((b0,b1),(a1))
with {
    transition_gain = sqrt(low_gain * high_gain);
    pi_transition_frequency = PI * transition_freq;
    zero = (high_gain * high_gain) + (low_gain * low_gain) - 2.0* (transition_gain * transition_gain);
    alpha = select2(zero != 0, 0, lambda - (lambda / fabs(lambda)) * sqrt((lambda * lambda) - 1.0));
    lambda = ((high_gain * high_gain) - (low_gain * low_gain)) / zero;

    beta0 = 0.5 * ((low_gain + high_gain) + (low_gain - high_gain) * alpha);
    beta1 = 0.5 * ((low_gain - high_gain) + (low_gain + high_gain) * alpha);
    rho = sin(pi_transition_frequency/2.0 - PI/4.0) / sin(pi_transition_frequency/2.0 + PI/4.0);

    b0 = (beta0 + rho*beta1) / (1.0 + rho*alpha);
    b1 = (beta1 + rho*beta0) / (1.0 + rho*alpha);
    a1 = (rho + alpha) / (1.0 + rho*alpha);     
};

receptivity_peak_filter(low_freq, high_freq, gain) = iir((b0,b1,b2),(a1,a2))
with {
    c1 = cos(PI * low_freq);
    c2 = cos(PI * high_freq);
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
sources(eta_d,Uj_d,Vac) = (eta_d,Uj_d,Vac) <: (_,_,!,!,_,_) : (jetDrive, turbulence, vortex) : (_,_+_+_);

// vortex
vortex(vac) = select2(vac > 0, -va2, va1) * VORTEX_CTE * vac * vac
with {
    va1 = 0.1;
    va2 = 4.99;
};

//tanh_slow = min(4.0) : max(-4.0) : tanh;

tanh_fast = min(4.0) : max(-4.0) : tanh_lookup
with {
   size = 8000;
   index = (+(1)~_ ) - 1; // 0,1,2,...
   tanh_creation = float(index) / size * 8.0 -4.0 : tanh;
   tanh_lookup(x) = rdtable(size+1, tanh_creation, int((x+4.0)/ 8.0 * size));
};

// jetDrive
// out : hyd_feed, jet_drive
jetDrive(jet_displacement, uj) = Qin <: hyd_constant * _, (jet_drive_cst * (_ - _'))
with {

    // FIXME
    Qin = uj * b * jet_width * (1.0 + tanh_fast(tanh_argument))
    with {
      tanh_argument = (jet_displacement - labium_position) / b;
      b = b_constant * jet_height;
      b_constant = 0.5; //.39 proportion between b and jet_height
    };

    hyd_constant = 2.0 * ratio * (kappa * kappa - 1.0) / (M_PI * (kappa * kappa + 1))
    with {
        ratio = delta_d / flue_labium_distance;
        beta = ratio + sqrt(ratio * (2.0 + ratio));
        kappa = 1.0 + beta;
    };

    jet_drive_cst = (-1 * AIR_DENSITY * delta_d) / (jet_width * flue_labium_distance * sampling_period);
   
    sampling_period = 1.0 / SR;

};


// turbulence
turbulence(uj) = turbulence_gain * MAX_AMPLITUDE * uj * uj * jet_height * filtered_noise
with {
   turbulence_gain = 1;

   // FIXME
   filtered_noise = noise : iir((b1,b2,b3),(a1,a2));

   a1 = -1.59164698202301;
   a2 = 0.69491246133220;
   b1 = 0.15254376933390;
   b2 = 0.0;
   b3 = -0.15254376933390;
};

//process = excitation;
