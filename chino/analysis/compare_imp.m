clear all; close all;
clc;

Fs=44100; % sample frequency
N=Fs/10;

f_hz=20:20000; % complete frequency range
f_range=20:5600; % useful frequency range
f_use=f_range(1:Fs/N:end);

%% Physical parameters
rho=1.2; % air volumetric mass
c=343.54;  % sound speed
beta=0.003; % losses parameter

%% Geometry
L1= 0.29; L2= 0.28; r1= 0.0095; r2= 0.0055;
p = [L1,L2,r1,r2,beta];

%% Computing
Ztheo=theoretical_imp(p,f_use);
Ytheo_dB=imp_to_adm(Ztheo);

Zsyn=faust_imp(p,f_use);
Ysyn_dB=imp_to_adm(Zsyn);

read=csvread('../Measurements/LMA_Grande.csv',2,0);
Zexp=read(1:2*Fs/N:end,2);
Yexp_dB=imp_to_adm(Zexp);

%% Compare theretical and exp
% semilogy(f_use,Yexp_dB,'k-',f_use,Ytheo_dB,'b-');
% legend('Experimental data','Theoretical model');
% title(sprintf('Input admittance of a complex resonator :\n comparison between theoretical model and experiment measurements'));
% axis([20 5600 -10^2 -10^0.8]);
% xlabel('frequency (Hz)'); ylabel('amplitude (dB)');


%% Compare theoretical and synthesis
% semilogy(f_use,Ytheo_dB,'b-',f_use,Ysyn_dB,'r-');
% legend('Theoretical model','FAUST simulation');
% title(sprintf('Input admittance of a complex resonator :\n comparison between theoretical model and FAUST simulation'));
% axis([20 5600 -10^2 -10^0.8]);
% xlabel('frequency (Hz)'); ylabel('amplitude (dB)');


%% Compare theoretical and synthesis
semilogy(f_use,Yexp_dB,'b-',f_use,Ysyn_dB,'r-');
legend('Experimental data','FAUST simulation');
title(sprintf('Input admittance of a complex resonator :\n comparison between experiment measurements and FAUST simulation'));
axis([20 5600 -10^2 -10^0.8]);
xlabel('frequency (Hz)'); ylabel('amplitude (dB)');
