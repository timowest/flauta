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

// excitation
pressure = hslider("pressure", 32, 254, 1, 1);

min_jet_vel = 1.0;
max_jet_vel = 40;
step_Uj = 0.1;
//flue_labium_distance = hslider("flue-labium dist", 4.0, 0.5, 13.0, 0.1) * 0.001;
flue_labium_distance = 0.001 * hslider("flue-labium dist", 4.0, 0.5, 13.0, 0.1);  
//flue_labium_distance = 0.004; 
max_flue_labium_d = 0.016;
labium_position = 0.0002; 
//labium_position = hslider("labium position", 2, 0, 12.7, 0.1) * 0.0001;
convection_f = 0.5;
min_convection_f = 0.3;
channel_length = hslider("channel length", 4e-3, 0.006, 0.132, 0.001); // 0.006 - 0.132
vibrato_freq = hslider("vibrato freq", 5.9, 0.0, 9.28125, 0.01); // 0.0 - 9.28125
vibrato_gain = hslider("vibrato gain", 0.0, 0.0, 1.54688, 0.001); // 0.0 - 1.54688
//vibrato_gain = hslider("vibrato gain", 0.0, 0.0, 1547, 1) * 0.001; // 0.0 - 1.54688
jet_height =  1.08e-3;
//jet_height =  0.00108; 
//jet_height = hslider("jet height", 1.08, 0.05, 1.27, 0.01) * 0.001; // 5e-05 - 0.00127
jet_width = 0.02;
delta_d = 1.0e-3;
//delta_d = 0.001;

turbulence_gain = 1;

// resonator
//cav_length = hslider("cavity length", 17.5, 10.0, 22.7, 0.1) * 0.001; // 0.01 - 0.0227
cav_length = hslider("cavity length", 0.0175, 0.01, 0.0227, 0.0001); // 0.01 - 0.0227
cav_radius = 0.0085;
//chim_length = hslider("chimney length", 10.0, 8, 20.7, 0.1) * 0.001; // 0.008 - 0.0207
chim_length = hslider("chimney length", 0.01, 0.008, 0.0207, 0.001); // 0.008 - 0.0207
chim_radius = 0.007;
end_length = 0.08;
end_radius = 0.007;
tub_length = 0.245; 
tub_radius = 0.009;

impulse_scale = 1;


