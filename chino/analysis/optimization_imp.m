%clear all; close all;
%clc;

Fs=44100; % sample frequency
f_hz=20:20000; % frequency range in Hertz
N=Fs; % output length
f_range=20:5600; % useful frequency range
f_use=f_range(1:Fs/N:end);
index=f_use*N/Fs;

%% Collecting experience data
% read=csvread('Measurements/LMA_Grande.csv',2,0);
% Zexp=read(1:2*Fs/N:end,2);

%file_name='Measurements/catarra.txt';
file_name='Measurements/segundera.txt';
%file_name='Measurements/puntera.txt';
Zexp=get_data(file_name,f_use);

Yexp_dB=imp_to_adm(Zexp');
Yexp_square=Yexp_dB.^2;

%% Initial parameters (m)
%L1= 0.28; L2= 0.28; r1= 0.0095; r2= 0.0055; beta=0.003; % LMA
%L1= 0.111; L2= 0.124; r1= 0.0085; r2= 0.00525; beta=0.003; % catarra
L1= 0.28; L2= 0.26; r1= 0.0075; r2= 0.005; beta=0.003; % segundera
%L1= 0.31; L2= 0.30; r1= 0.009; r2= 0.0055; beta=0.003; % puntera

p_ini=[L1,L2,r1,r2,beta];

%% Optimization
LB=[0.1,0.1,0.001,0.001,0.001];
UB=[0.4,0.4,0.01,0.01,0.006];
options=optimset('DiffMinChange',1e-4,'TolFun',1e-16,'TolX',1e-16,'MaxFunEvals',1500,'MaxIter',8000);

p_opt=lsqcurvefit('faust_adm_square',p_ini,Yexp_dB,Yexp_square,LB,UB,options);

%% Computing synthesis admittances
Yini_syn_dB=imp_to_adm(faust_imp(p_ini,f_use));
Yopt_syn_dB=imp_to_adm(faust_imp(p_opt,f_use));


%% Visualizing results

semilogy(f_use,Yexp_dB,'k-',f_use,Yini_syn_dB,'b-',f_use,Yopt_syn_dB,'r-');
title('Input admittance of a complex resonator : result of FAUST synthesis optimization on puntera');
legend('Experimental measurements','Initial FAUST synthesis','Optimized FAUST synthesis');
xlabel('frequency (Hz)'); ylabel('amplitude (dB)');
V=axis;
axis([V(1) V(2) -10^(2.1) -10^(0.85)]);
