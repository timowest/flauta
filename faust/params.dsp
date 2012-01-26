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

// EXCITATION

gate = button("gate");

// Pressure

human_control_flag = checkbox("h:h2/h:res/Automatic pressure (StrW)");

pressure = select2(human_control_flag, pressure_fij, calculated_pressure);

calculated_pressure = pow(curr_freq * w/strW, 2) * rho/2
with {
  curr_freq = freq;
  rho = 1.2;
  w = flue_labium_distance;
  strW  = vslider("h:h2/h:res/StrW", 25, 1, 100, 1) * 0.01;
};

manual_pressure = coarse + fine
with {
  coarse = vslider("h:h1/h:exc/pressure coarse", 16, 0, 127, 1) * 2;
  fine = vslider("h:h1/h:exc/pressure fine", 0, 0, 99, 1) * 0.1;
};

//JET
channel_length = vslider("h:h1/h:exc/h:Jet/channel len", 23, 1, 127, 1) + 5 * 0.001; 
jet_height = vslider("h:h1/h:exc/h:Jet/jet hgt", 100, 5, 127, 1) * 0.00001; 
jet_shape = vslider("h:h1/h:exc/h:Jet/jet shp", 90, 5, 127, 1) / 127.0;
flue_labium_distance = vslider("h:h1/h:exc/h:Jet/fl-la dist", 44, 5, 127, 1) * 0.0001;
max_flue_labium_d = 0.016;
labium_position = vslider("h:h1/h:exc/h:Jet/lab pos", 20, 0, 127, 1) * 0.00001;

min_jet_vel = 1.0;
max_jet_vel = 40;
step_Uj = 0.1;
convection_f = 0.5;
min_convection_f = 0.3;
jet_width = 0.02;

//SOURCES 
turbulence_gain = vslider("h:h1/h:exc/h:Sources/turb gain", 16, 0, 127, 1) * 50;
vortex_ampli1 = vslider("h:h1/h:exc/h:Sources/h:Vortex/Vor a1", 30, 0, 127, 1) * 0.1;
vortex_ampli2 = vslider("h:h1/h:exc/h:Sources/h:Vortex/Vor a2", 50, 0, 127, 1) * 0.1;
delta_d = vslider("h:h1/h:exc/h:Sources/Jet drive", 35, 0, 127, 1) * 0.0001;
impulse_scale = 1; //impulse_scale = vslider("h:h1/h:exc/h:Sources/impulse scale", 40, 0, 127, 1);

// ENVELOPE
env_attack = vslider("h:h1/h:env/attack", 5, 1, 100, 1) * 0.001;
env_decay = vslider("h:h1/h:env/decay", 10, 0, 1000, 10) * 0.001;
env_sustain = vslider("h:h1/h:env/sustain", 100, 10, 100, 1);
env_release = vslider("h:h1/h:env/release", 10, 0, 1000, 10) * 0.001;

// VIBRATO
vibrato_freq = vslider("h:h2/h:vib/freq", 0.0, 0.0, 99, 1) * ONE_OVER_128 * 12.0; 
vibrato_gain = vslider("h:h2/h:vib/gain", 0.0, 0.0, 99, 1) * ONE_OVER_128 * 2.0; 
vib_attack = vslider("h:h2/h:vib/attack", 5, 1, 100, 1) * 0.001;
vib_decay = vslider("h:h2/h:vib/decay", 10, 0, 1000, 10) * 0.001;
vib_sustain = vslider("h:h2/h:vib/sustain", 100, 10, 100, 1);
vib_release = vslider("h:h2/h:vib/release", 10, 0, 1000, 10) * 0.001;

// RESONATOR
end_samples = end_length * SR / TWO_SOUND_SPEED;
cavity_samples = cav_length * SR / TWO_SOUND_SPEED;
chimney_samples = chim_length * SR / TWO_SOUND_SPEED;
// tube length is dependent on desired frequency
tube_samples = SR / (freq - RAD_ORDER - VT_ORDER);

cav_length = 0.010 + (vslider("h:h2/h:res/cavity len", 40, 0, 127, 1) * 0.0001); 
cav_radius = 0.0085;
chim_length = 0.008 + (vslider("h:h2/h:res/chimney len", 60, 0, 127, 1) * 0.0001); 
chim_radius = 0.007;
end_length = vslider("h:h2/h:res/end len", 8, 1, 20, 0.1) * 0.01;
end_radius = vslider("h:h2/h:res/end rad", 7, 1, 20, 0.1) * 0.001;
//tub_length = vslider("h:h2/h:res/tube len", 245, 240, 250, 1) * 0.001;
tub_radius = 0.009;

freq = vslider("h:h2/h:res/Note", 76, 1, 127, 1) : midiToFreq;

//MIDItoFREQ
midiToFreq(n) = 440 * pow(2, (n-69)/12);


