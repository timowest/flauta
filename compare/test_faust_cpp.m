clear all; close all; clc;

bernoulli_cpp=get_data_cpp('bernoulli');
blow_cpp=get_data_cpp('blow');
excitation_cpp=get_data_cpp('excitation');
jet_cpp=get_data_cpp('jet');
jetdrive_cpp=get_data_cpp('jetdrive');
receptivity_cpp=get_data_cpp('receptivity');
resonator_cpp=get_data_cpp('resonator');
sources_cpp=get_data_cpp('sources');
turbulence_cpp=get_data_cpp('turbulence');
vortex_cpp=get_data_cpp('vortex');

bernoulli_faust=get_data_faust('bernoulli');
bernoulli=abs(bernoulli_faust-bernoulli_cpp);

blow_faust=get_data_faust('blow');
blow=abs(blow_faust-blow_cpp);

excitation_faust=get_data_faust('excitation');
excitation=abs(excitation_faust-excitation_cpp);

jet_faust=get_data_faust('jet');
jet=abs(jet_faust-jet_cpp);

jetdrive_faust=get_data_faust('jetdrive');
jetdrive=abs(jetdrive_faust-jetdrive_cpp);

receptivity_faust=get_data_faust('receptivity');
receptivity=abs(receptivity_faust-receptivity_cpp);

resonator_faust=get_data_faust('resonator');
resonator=abs(resonator_faust-resonator_cpp);

sources_faust=get_data_faust('sources');
sources=abs(sources_faust-sources_cpp);

turbulence_faust=get_data_faust('turbulence');
turbulence=abs(turbulence_faust-turbulence_cpp);

vortex_faust=get_data_faust('vortex');
vortex=abs(vortex_faust-vortex_cpp);