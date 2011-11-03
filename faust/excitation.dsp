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
import("utils.dsp");

// out : sources, impulse
excitation(Vac,Pp) = (Vac,Pp) <: (_,_,_,!)
    : (_,(blow : (limit, limit, _)),_) 
    : ((jet,_,_)
    <: (_,_,!,_,!,!,_,!)
    : (sources, _)) ~ _
    : (!,_+_);

limit = max(min_jet_vel) : min(max_jet_vel);

// blow
// in : mouth pressure
// out : uj, uj_steady, impulse
blow = (((envelope * target_driving_pressure) <: (_ + (vibrato_gain * vibrato) * _) : max(0)),_ ) 
    : bernoulli : (max(0), max(0), _)
with {
    target_driving_pressure = pressure;

    // TODO : parametrize
    envelope = gate : adsr(0.005 * SR, 0.01, 100, 0.01);

    // XXX : vibrato envelope missing
    vibrato = vibrato_gain * osc(vibrato_freq); 
};


// bernoulli
// in : pressure_in, pressure_out
// out : bernoulli, uj_steady, impulse
bernoulli = (_,_) <: ((curr_velocity ~ _), ((curr_velocity_steady ~ _), !)) 
    // in : cv, cvp, cvs
    <: (_,!,_,impulse(_, _),!)
with {
    curr_velocity(prev) = prev + (const_bernoulli * ((_- _) - (HALF_DENSITY * (prev * prev)))), prev;

    curr_velocity_steady(prev) = prev + (const_bernoulli * (_ - (HALF_DENSITY * (prev * prev)))); 

    // in : cv, cvp
    impulse = const_impulse * (_- _) : max(0) : min(max_impulse);

    const_impulse = impulse_scale * (SR * AIR_DENSITY * 0.61 * chim_radius);

    max_impulse = 500;

    const_bernoulli = 1 / (SR * AIR_DENSITY * channel_length);
};

// out : eta_d, Uj_d
jet(Qin,Vac,Uj_steady,Uj) = (Qin,Vac,Uj_steady,Uj) : (receptivity,_) : (jetDelay, jetDelay)
with {
    // XXX : make sure this is correct
    //delay_length = floor((max_flue_labium_d / (min_convection_f * min_jet_vel)) / SR);
    delay_length = jet_msamples_per_sec/ Uj_steady;

    jet_msamples_per_sec = flue_labium_distance / (convection_f * SR);

    jetDelay = fdelay(MAX_DELAY_LENGTH, delay_length);
};

receptivity(qin, vac, uj_steady) = excitation : jet_filter_peak1 : jet_filter_peak2 : jet_filter_shelf
with {
    excitation = TWO_div_M_PI * vac + qin;

    jet_filter_peak1 = receptivity_peak_filter(
        0.0645*(uj_steady/jet_height)*(2/(2*PI*SR)),
        0.3275*(uj_steady/jet_height)*(2/(2*PI*SR)),
        pow(10,2.6337*(flue_labium_distance / jet_height)/20));

    jet_filter_peak2 = receptivity_peak_filter(
        0.3278*(uj_steady/jet_height)*(2/(2*PI*SR)),
        1.2006*(uj_steady/jet_height)*(2/(2*PI*SR)),
        pow(10,5.0719*(flue_labium_distance / jet_height)/20));

    jet_filter_shelf = receptivity_shelf_filter(
        0.2954*(uj_steady/jet_height)*(2/(2*PI*SR)),
        pow(10,2.3884*(flue_labium_distance/jet_height)/20),
        pow(10,0.0*(flue_labium_distance/jet_height)/20));

    //jet_filter_one_over_omega = _; 
};

receptivity_shelf_filter(transition_freq, low_gain, high_gain) = tf2(b0,b1,b2,a1,a2)
with {
    transition_gain = sqrt(low_gain * high_gain);
    pi_transition_frequency = PI * transition_freq;
    zero = (high_gain * high_gain) + (low_gain * low_gain) - 2* (transition_gain * transition_gain);
    alpha = select2(zero != 0, 0, lambda - (lambda / abs(lambda)) * sqrt((lambda * lambda) - 1));
    lambda = ((high_gain * high_gain) - (low_gain * low_gain)) / zero;

    beta0 = 0.5 * ((low_gain + high_gain) + (low_gain - high_gain) * alpha);
    beta1 = 0.5 * ((low_gain - high_gain) + (low_gain + high_gain) * alpha);
    rho = sin(pi_transition_frequency/2 - PI/4) / sin(pi_transition_frequency/2 + PI/4);

    b0 = 1;
    b1 = (beta0 + rho*beta1) / (1 + rho*alpha);
    b2 = (beta1 + rho*beta0) / (1 + rho*alpha);
    a1 = 1;
    a2 = (rho + alpha) / (1 + rho*alpha);     
};

receptivity_peak_filter(low_freq, high_freq, gain) = tf3(b0,b1,b2,b3,a1,a2,a3)
with {
    c1 = cos(PI * low_freq);
    c2 = cos(PI * high_freq);
    beta = (1 + c1*c2) / (c1+c2);
    wc = acos(beta - (beta/abs(beta))*sqrt((beta*beta)-1));
    cc = cos(wc);
    sc = sin(wc);

    Q = sqrt(gain * sc*sc * (c1+c2) / (4 * (2*cc - c1 - c2)));
    k = (2*Q - sc) / (2*Q + sc);

    b0 = 1;
    b1 = ((1+k) + gain*(1-k))/2;
    b2 = -cc*(1+k);
    b3 = ((1+k) - gain*(1-k))/2;
    a1 = 1;
    a2 = -cc*(1+k);
    a3 = k;
    
};

sources(eta_d,Uj_d,Vac) = (eta_d,Uj_d,Vac) <: (_,_,!,!,_,_) : (jetDrive, turbulence, vortex) : (_,_+_+_);

// vortex
vortex(vac) = select2(vac > 0, -va2, va1) * VORTEX_CTE * vac * vac
with {
    va1 = 0.1;
    va2 = 4.99;
};

// jetDrive
// out : hyd_feed, jet_drive
jetDrive(jet_displacement, uj) = Qin <: hyd_constant * _, (jet_drive_cst * (_ - _'))
with {

    Qin = uj * b * jet_width * (1.0 + tanh(tanh_argument));
    
    tanh_argument = (jet_displacement - labium_position) / b;

    hyd_constant = 2.0 * ratio * (kappa * kappa - 1.0) / (M_PI * (kappa * kappa + 1))
    with {
        ratio = delta_d / flue_labium_distance;
        beta = ratio + sqrt(ratio * (2.0 + ratio)); 
        kappa = 1.0 + beta;
    };

    jet_drive_cst = (-1 * AIR_DENSITY * delta_d) / (jet_width * flue_labium_distance * sampling_period);

    b = b_constant * jet_height;
    b_constant = 0.5; //.39 proportion between b and jet_height
   
    sampling_period = 1.0 / SR;

};

// turbulence
turbulence(uj) = turbulence_gain * MAX_AMPLITUDE * uj * uj * jet_height * filtered_noise
with {
   turbulence_gain = 1;

   // FIXME
   filtered_noise = noise : tf3(b0,b1,b2,b3,a1,a2,a3);

   a1 = 1.0;
   a2 = -1.59164698202301;
   a3 = 0.69491246133220;
   b0 = 1.0;
   b1 = 0.15254376933390;
   b2 = 0.0;
   b3 = -0.15254376933390;
};

//process = excitation;
