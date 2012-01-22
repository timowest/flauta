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

pressure = vslider("h:h1/h:exc/pressure", 32, 1, 254, 1);

min_jet_vel = 1.0;
max_jet_vel = 40;
step_Uj = 0.1;

flue_labium_distance = vslider("h:h1/h:exc/fl-la dist", 4.4, 0.5, 13.0, 0.1) * 0.001;
max_flue_labium_d = 0.016;
labium_position = vslider("h:h1/h:exc/lab pos", 2, 0, 12.7, 0.1) * 0.0001;
convection_f = 0.5;
min_convection_f = 0.3;
channel_length = vslider("h:h1/h:exc/channel len", 0.004, 0.006, 0.132, 0.001); // 0.006 - 0.132 
jet_height = vslider("h:h1/h:exc/jet hgt", 1.08, 0.05, 1.27, 0.01) * 0.001; // 5e-05 - 0.00127
jet_width = 0.02;
delta_d = 0.001;
impulse_scale = vslider("h:h1/h:exc/impulse scale", 1.0, 0.1, 10, 0.1);
turbulence_gain = vslider("h:h1/h:exc/turb gain", 50, 0, 6350, 50);

// ENVELOPE

env_attack = vslider("h:h1/h:env/attack", 5, 1, 100, 1) * 0.001;
env_decay = vslider("h:h1/h:env/decay", 10, 0, 1000, 10) * 0.001;
env_sustain = vslider("h:h1/h:env/sustain", 100, 10, 100, 1);
env_release = vslider("h:h1/h:env/release", 10, 0, 1000, 10) * 0.001;

// VIBRATO

vibrato_freq = vslider("h:h2/h:vib/freq", 0.0, 0.0, 9.28125, 0.01); // 0.0 - 9.28125 check
vibrato_gain = vslider("h:h2/h:vib/gain", 0.0, 0.0, 1547, 1) * 0.001; // 0.0 - 1.54688 check

vib_attack = vslider("h:h2/h:vib/attack", 5, 1, 100, 1) * 0.001;
vib_decay = vslider("h:h2/h:vib/decay", 10, 0, 1000, 10) * 0.001;
vib_sustain = vslider("h:h2/h:vib/sustain", 100, 10, 100, 1);
vib_release = vslider("h:h2/h:vib/release", 10, 0, 1000, 10) * 0.001;

// RESONATOR

cav_length = vslider("h:h2/h:res/cavity len", 17.5, 10.0, 22.7, 0.1) * 0.001; // 0.01 - 0.0227
cav_radius = 0.0085;
chim_length = vslider("h:h2/h:res/chimney len", 10.0, 8, 20.7, 0.1) * 0.001; // 0.008 - 0.0207
chim_radius = 0.007;
end_length = vslider("h:h2/h:res/end len", 8, 1, 20, 0.1) * 0.01;
end_radius = vslider("h:h2/h:res/end rad", 7, 1, 20, 0.1) * 0.001;
tub_length = vslider("h:h2/h:res/tube len", 245, 240, 250, 1) * 0.001;
tub_radius = 0.009;




