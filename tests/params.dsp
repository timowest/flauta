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

// VERSION FOR TESTING

dac_scale = 0.007;

// parameters

gate = 1.0;

// EXCITATION

pressure = 32.0;

//JET
channel_length = 1e-2;
jet_height = 2.0e-3; 
jet_shape = 0.5; // used as b_constant in jet_drive
flue_labium_distance = 1e-2;
max_flue_labium_d = 0.016;
labium_position = 0.0001;

min_jet_vel = 1.0;
max_jet_vel = 40.0;
step_Uj = 0.1;
convection_f = 0.5;
min_convection_f = 0.3;
jet_width = 0.02;

//SOURCES 
turbulence_gain = 1.0;
vortex_ampli1 = 0.1;
vortex_ampli2 = 4.99;
delta_d = 1.0e-3;
impulse_scale = 1.0;

// ENVELOPE
env_attack = 0.005;
env_decay = 0.01;
env_sustain = 1.0;
env_release = 0.01;

// VIBRATO
vibrato_freq = 5.9; 
vibrato_gain = 0.0;

// RESONATOR
end_samples = end_length * SR / TWO_SOUND_SPEED;
cavity_samples = cav_length * SR / TWO_SOUND_SPEED;
chimney_samples = chim_length * SR / TWO_SOUND_SPEED;
tube_samples = tub_length * SR / TWO_SOUND_SPEED;

cav_length = 0.0175; 
cav_radius = 0.0085;
chim_length = 0.01; 
chim_radius = 0.007;
end_length = 0.08;
end_radius = 0.007;
tub_length = 0.245;
tub_radius = 0.009;



