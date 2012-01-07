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

gate = button("gate");

// EXCITATION

pressure = hslider("pressure", 32, 1, 254, 1); //check

min_jet_vel = 1.0;
max_jet_vel = 40;
step_Uj = 0.1;
flue_labium_distance = hslider("flue-labium dist", 4.4, 0.5, 13.0, 0.1) * 0.001;
//flue_labium_distance = 0.004; // is 0.0044 
max_flue_labium_d = 0.016;
labium_position = hslider("labium position", 2, 0, 12.7, 0.1) * 0.0001;
//labium_position = 0.0002; 
convection_f = 0.5;
min_convection_f = 0.3;
channel_length = hslider("channel length", 0.004, 0.006, 0.132, 0.001); // 0.006 - 0.132 // CHANGED TO 0.004 and SOUNDS! Thanks Beer ;)

vibrato_freq = hslider("vibrato freq", 0.0, 0.0, 9.28125, 0.01); // 0.0 - 9.28125 check
vibrato_gain = hslider("vibrato gain", 0.0, 0.0, 1547, 1) * 0.001; // 0.0 - 1.54688 check

//vibrato_gain = hslider("vibrato gain", 0.0, 0.0, 1.54688, 0.001); // 0.0 - 1.54688
jet_height = hslider("jet height", 1.08, 0.05, 1.27, 0.01) * 0.001; // 5e-05 - 0.00127
//jet_height =  0.00108; 
jet_width = 0.02;
delta_d = 1.0e-3;
//delta_d = 0.001;

turbulence_gain = 50; // value should be from 1 to 6350 in steps of 50 hslider("Turbulence", 0, 0, 6350, 50); dont know why doesnt work! ¬¬ stupid slider

env_attack = hslider("env attack", 5, 1, 100, 1) * 0.001;
env_decay = hslider("env decay", 10, 0, 1000, 10) * 0.001;
env_sustain = hslider("env sustain", 100, 10, 100, 1);
env_release = hslider("env release", 10, 0, 1000, 10) * 0.001;

vib_attack = hslider("vib attack", 5, 1, 100, 1) * 0.001;
vib_decay = hslider("vib decay", 10, 0, 1000, 10) * 0.001;
vib_sustain = hslider("vib sustain", 100, 10, 100, 1);
vib_release = hslider("vib release", 10, 0, 1000, 10) * 0.001;

// RESONATOR

cav_length = hslider("cavity length", 14.0, 10.0, 22.7, 0.1) * 0.001; // 0.01 - 0.0227 //change 17.5 to 14.0
//cav_length = hslider("cavity length", 0.0175, 0.01, 0.0227, 0.0001); // 0.01 - 0.0227
cav_radius = 0.0085;
chim_length = hslider("chimney length", 14.0, 8, 20.7, 0.1) * 0.001; // 0.008 - 0.0207 change 10.0 to 14.0
//chim_length = hslider("chimney length", 0.01, 0.008, 0.0207, 0.001); // 0.008 - 0.0207
chim_radius = 0.007;
end_length = hslider("end length", 8, 1, 20, 0.1) * 0.01;
//end_length = 0.08 ;
end_radius = hslider("end_radius", 7, 1, 20, 0.1) * 0.001;
//end_radius = 0.007;
tub_length = hslider("tube length", 245, 240, 250, 1) * 0.001;
//tub_length = 0.245; 
tub_radius = 0.009;

impulse_scale = 40;


