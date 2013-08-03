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


// parameters

// FLAUTA

dac_scale = vslider("h:h2/volume", 7, 0, 10, 0.01) * 0.001;


// EXCITATION

gate = checkbox("h:h2/gate");

// Pressure
pressure = coarse + fine
with {
  coarse = vslider("h:exc/h:pressure/coarse", 26, 0, 127, 1);
  fine = vslider("h:exc/h:pressure/fine", 38, 0, 99, 1) * 0.1;
};

//JET
channel_length = (vslider("h:exc/h:Jet/chan_len", 122, 1, 127, 1)+5)*0.001; 
jet_height = vslider("h:exc/h:Jet/jet_hgt", 118, 5, 127, 1) * 0.00001; 
jet_shape = vslider("h:exc/h:Jet/jet_shp", 121, 5, 127, 1)/127;
flue_labium_distance = vslider("h:exc/h:Jet/fl-la_dist", 13.7, 1, 16, 0.1)*0.001;
max_flue_labium_d = 0.016;
labium_position = vslider("h:exc/h:Jet/lab_pos", 8, 0, 127, 1)*0.00001;

min_jet_vel = 1.0;
max_jet_vel = 40;
step_Uj = 0.1;
convection_f = 0.5;
min_convection_f = 0.3;
jet_width = 0.02; // TODO : make jet width controllable (input * 0.001)


//SOURCES 
turbulence_gain = vslider("h:exc/h:Sources/turb_gain", 16, 0, 227, 1) * 50 * 800;
vortex_ampli1 = vslider("h:exc/h:Sources/h:Vortex/Vor_a1", 42, 0, 127, 1) * 0.1;
vortex_ampli2 = vslider("h:exc/h:Sources/h:Vortex/Vor_a2", 39, 0, 127, 1) * 0.1;
delta_d = vslider("h:exc/h:Sources/Jet_drive", 125, 0, 127, 1) * 0.0001;
impulse_scale = 1;

// RESONATOR
length1 = vslider("h:h2/h:res/Len1", 0.016, 0.01, 0.200, 0.001);
length2 = vslider("h:h2/h:res/Len2", 0.021, 0.01, 0.200, 0.001);
length3 = vslider("h:h2/h:res/Len3", 0.077, 0.01, 0.200, 0.001);
radius1 = vslider("h:h2/h:res/Rad1", 0.0085, 0.001, 0.020, 0.001);
radius2 = vslider("h:h2/h:res/Rad2", 0.00115, 0.001, 0.020, 0.001);
radius3 = vslider("h:h2/h:res/Rad3", 0.006, 0.001, 0.020, 0.001);

  lossescoef = vslider("h:h2/h:res/losses", 3.13, 0.0, 7, 0.01)*0.00001;
  rad_coef = vslider("h:h2/h:res/radiation", 0.6133, 0.6133, 0.8488, 0.0001);


// ENVELOPE
env_attack = vslider("h:h2/h:env/attack", 0, 0, 99, 1) * 0.02;
env_decay = vslider("h:h2/h:env/decay", 0, 0, 99, 1) * 0.001;
env_sustain = vslider("h:h2/h:env/sustain", 100, 10, 100, 1);
env_release = vslider("h:h2/h:env/release", 0, 0, 99, 1) * 0.02;

// VIBRATO
vibrato_gain = vslider("h:h2/h:vib/gain", 0.0, 0.0, 99, 0.1)* ONE_OVER_128 /2 ;
vibrato_freq = vslider("h:h2/h:vib/freq", 0.0, 0.0, 20, 0.1) ;
