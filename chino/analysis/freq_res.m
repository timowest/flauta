clear all; close all;
clc;

Fs=44100; % sample frequency
N=Fs/10;

rho=1.2; % air volumetric mass
c=343.54;  % sound speed
beta=0.003; % losses parameter

f_hz=20:20000; % complete frequency range
f_range=20:5600; % useful frequency range
f_use=f_range(1:Fs/N:end);

L1= 0.28;
L2= 0.28;
r1= 0.0095;
r2= 0.0055;

partial=[1 2 4 5 7 8 10 11 13 14 16 17 19 20 22 23 25 26 28 29 31 32 34 35 37 38 40];

%% Theoretical inharmonicity
% 
% [Ztheow,Ztheo]=theoretical_imp([L1,L2,r1,0.0052,beta],f_use);
% [Ztheow2,Ztheo2]=theoretical_imp([L1,L2,r1,0.0053,beta],f_use);
% [Ztheow3,Ztheo3]=theoretical_imp([L1,L2,r1,0.0054,beta],f_use);
% 
% %without losses
% Ytheow=1./Ztheow;
% Ytheow_dB=20*log10(Ytheow/norm(Ytheow));
% Ytheow2=1./Ztheow2;
% Ytheow2_dB=20*log10(Ytheow2/norm(Ytheow2));
% Ytheow3=1./Ztheow3;
% Ytheow3_dB=20*log10(Ytheow3/norm(Ytheow3));
% 
% [p_theow,f_theow] = calc_inharm(Ytheow_dB,f_use,partial);
% [p_theow2,f_theow2] = calc_inharm(Ytheow2_dB,f_use,partial);
% [p_theow3,f_theow3] = calc_inharm(Ytheow3_dB,f_use,partial);
% 
% %with losses
% Ytheo=1./Ztheo;
% Ytheo_dB=20*log10(Ytheo/norm(Ytheo));
% Ytheo2=1./Ztheo2;
% Ytheo2_dB=20*log10(Ytheo2/norm(Ytheo2));
% Ytheo3=1./Ztheo3;
% Ytheo3_dB=20*log10(Ytheo3/norm(Ytheo3));
% 
% [p_theo,f_theo] = calc_inharm(Ytheo_dB,f_use,partial);
% [p_theo2,f_theo2] = calc_inharm(Ytheo2_dB,f_use,partial);
% [p_theo3,f_theo3] = calc_inharm(Ytheo3_dB,f_use,partial);

%% Synthesis inharmonicity
Zsyn=faust_imp([L1,L2,r1,r2,beta],f_use);
Ysyn=1./Zsyn;
Ysyn_dB=20*log10(Ysyn/norm(Ysyn));
[p_syn,f_syn] = calc_inharm(Ysyn_dB,f_use,partial);

%% Experimental inharmonicity (LMA)
read=csvread('Measurements/LMA_Grande.csv',2,0);
Zexp=read(1:2*Fs/N:end,2);
Yexp=1./Zexp;
Yexp_dB=20*log10(Yexp/norm(Yexp));

[p_LMA,f_LMA] = calc_inharm(Yexp_dB,f_use,partial);

%% Experimental inharmonicity (pifilcas)
Zcat=get_data('Measurements/catarra.txt',f_use);
Zseg=get_data('Measurements/segundera.txt',f_use);
Zpun=get_data('Measurements/puntera.txt',f_use);

Ycat=1./Zcat;
Ycat_dB=20*log10(Ycat/norm(Ycat));
[p_cat,f_cat] = calc_inharm(Ycat_dB,f_use,partial);

Yseg=1./Zseg;
Yseg_dB=20*log10(Yseg/norm(Yseg));
[p_seg,f_seg] = calc_inharm(Yseg_dB,f_use,partial);

Ypun=1./Zpun;
Ypun_dB=20*log10(Ypun/norm(Ypun));
[p_pun,f_pun] = calc_inharm(Ypun_dB,f_use,partial);


%% Ploting without losses

% plot(p_theow,f_theow,'+',p_theow2,f_theow2,'o',p_theow3,f_theow3,'x');
% xlabel('partial number'); ylabel('inharmonicity');
% title(sprintf('Distance of each partial to the harmonic equivalent \n considering an harmonic serie with one third of the partials missing : \n Theoretical case without losses'));
% legend('r2=5.2 mm','r2=5.5 mm','r2=5.8 mm');


%% Ploting with losses
% 
% plot(p_theo,f_theo,'+',p_theo2,f_theo2,'o',p_theo3,f_theo3,'x');
% xlabel('partial number'); ylabel('inharmonicity');
% title(sprintf('Distance of each partial to the harmonic equivalent \n considering an harmonic serie with one third of the partials missing : \n Theoretical case with losses'));
% legend('r2=5.2 mm','r2=5.3 mm','r2=5.4 mm');


%% Ploting exp pifilcas
% 
% plot(p_cat,f_cat,'+',p_seg,f_seg,'o',p_pun,f_pun,'x',p_LMA,f_LMA,'x');
% xlabel('partial number'); ylabel('inharmonicity');
% title(sprintf('Distance of each partial to the harmonic equivalent \n considering an harmonic serie with one third of the partials missing : \n Experimental measurements'));
% legend('Catarra','Segundera','Puntera','LMA');


%% Ploting synthesis

plot(p_syn,f_syn,'+');
xlabel('partial number'); ylabel('inharmonicity');
title(sprintf('Distance of each partial to the harmonic equivalent \n considering an harmonic serie with one third of the partials missing : \n Synthesis signal'));
