%clear all; close all;
%clc;

Fs=44100; % sample frequency
f_hz=20:20000; % frequency range in Hertz
N=Fs/10; % output length
f_range=20:5600; % useful frequency range
f_use=f_range(1:Fs/N:end);
index=f_use*N/Fs;

%% Collecting experience data

file_name='../Measurements/antara14.csv';
%file_name='../Measurements/antara24.csv';
%file_name='../Measurements/antara34.csv';
%file_name='../Measurements/antara44.csv';

Zexp=get_data(file_name,f_use);
Yexp_dB=imp_to_adm(Zexp');
Yexp_square=Yexp_dB.^2;

%% Initial parameters of antara tubes

L1= 0.020; L2= 0.048; L3= 0.109 ; r1= 0.016; r2= 0.019; r3= 0.013; beta=0.003;
%L1= 0.028; L2= 0.055; L3= 0.116 ; r1= 0.016; r2= 0.020; r3= 0.013; beta=0.003;
%L1= 0.028; L2= 0.064; L3= 0.137 ; r1= 0.016; r2= 0.020; r3= 0.013; beta=0.003;
%L1= 0.030; L2= 0.076; L3= 0.154 ; r1= 0.017; r2= 0.022; r3= 0.013; beta=0.003;

p_ini=[L1,L2,L3,r1,r2,r3,beta];

%% Optimization
LB=[0.015,0.04,0.05,0.01,0.015,0.010,0.001];
UB=[0.04,0.08,0.2,0.02,0.020,0.015,0.009];
options=optimset('DiffMinChange',1e-3,'TolFun',1e-20,'TolX',1e-20,'MaxFunEvals',2000,'MaxIter',1000);

p_opt=lsqcurvefit('faust_adm_square',p_ini,Yexp_dB,Yexp_square,LB,UB,options);

%% Computing synthesis admittances
Yini_syn_dB=imp_to_adm(faust_imp(p_ini,f_use));
Yopt_syn_dB=imp_to_adm(faust_imp(p_opt,f_use));

%% Visualizing results

semilogy(f_use,[Yexp_dB' Yini_syn_dB Yopt_syn_dB]);
title('Input admittance of a 3 sections antara : result of FAUST synthesis (tube 1/4)');
legend('Experimental measurements','Initial FAUST synthesis','Optimized FAUST synthesis');
xlabel('frequency (Hz)'); ylabel('amplitude (dB)');
%V=axis;
%axis([V(1) V(2) -10^(2.1) -10^(0.85)]);
