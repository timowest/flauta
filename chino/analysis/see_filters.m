clear all; close all;
clc;

Fs=44100; % sample frequency
f=20:20000; % frequency range in Hertz
ff=f(1:6000);

rho=1.2; % air volumetric mass
c=343.54;  % sound speed

%% Geometry
r1=0.0095;
r2=0.0045;
L1=0.28;
L2=0.27;

%% Losses : comparison of numerical filters for different approx

% [Hlt,Hln1,Hln2,Hln3]=losses_filter(r1,r2,L1,L2,Fs,f);
% Hlt_mod=20*log10(abs(Hlt(ff))); Hlt_angle=angle(Hlt(ff));
% Hln1_mod=20*log10(abs(Hln1(ff))); Hln1_angle=angle(Hln1(ff));
% Hln2_mod=20*log10(abs(Hln2(ff))); Hln2_angle=angle(Hln2(ff));
% Hln3_mod=20*log10(abs(Hln3(ff))); Hln3_angle=angle(Hln3(ff));
% 
% subplot(2,1,1);
% semilogy(ff,Hlt_mod,'b-',ff,Hln1_mod,'m-.',ff,Hln2_mod,'r:',ff,Hln3_mod,'k--');
% legend('theoretical','numerical filter 1','numerical filter 2','numerical filter 3');
% xlabel('frequency (Hz)'); ylabel('amplitude (dB)'); 
% title('Losses coefficient for different approximations');
% subplot(2,1,2);
% semilogy(ff,Hlt_angle,'b-',ff,Hln1_angle,'m-.',ff,Hln2_angle,'r:',ff,Hln3_angle,'k--');
% xlabel('frequency (Hz)'); ylabel('phase');

%% Losses : comparison of numerical filters varying r1

% [Hltm,~,~,Hlnm]=losses_filter(0.002,r2,L1,L2,Fs,f);
% [Hltp,~,~,Hlnp]=losses_filter(0.10,r2,L1,L2,Fs,f);
% 
% Hltm_mod=20*log10(abs(Hltm(ff))); Hltm_angle=angle(Hltm(ff));
% Hlnm_mod=20*log10(abs(Hlnm(ff))); Hlnm_angle=angle(Hlnm(ff));
% Hltp_mod=20*log10(abs(Hltp(ff))); Hltp_angle=angle(Hltp(ff));
% Hlnp_mod=20*log10(abs(Hlnp(ff))); Hlnp_angle=angle(Hlnp(ff));
% 
% subplot(2,1,1);
% semilogx(ff,Hltp_mod,'b--',ff,Hlnp_mod,'b-',ff,Hltm_mod,'r--',ff,Hlnm_mod,'r-');
% legend('theoretical r1=10 cm','numerical filter r1=10 cm','theoretical r1=2 mm','numerical filter r1=2 mm');
% xlabel('frequency (Hz)'); ylabel('amplitude (dB)'); 
% title('Losses coefficient with variations on r1');
% subplot(2,1,2);
% semilogx(ff,Hltp_angle,'b--',ff,Hlnp_angle,'b-',ff,Hltm_angle,'r--',ff,Hlnm_angle,'r-');
% xlabel('frequency (Hz)'); ylabel('phase');

%% Losses : comparison of numerical filters varying L1
% 
% [Hltm,~,~,Hlnm]=losses_filter(r1,r2,0.05,L2,Fs,f);
% [Hltp,~,~,Hlnp]=losses_filter(r1,r2,0.50,L2,Fs,f);
% 
% Hltm_mod=20*log10(abs(Hltm(ff))); Hltm_angle=angle(Hltm(ff));
% Hlnm_mod=20*log10(abs(Hlnm(ff))); Hlnm_angle=angle(Hlnm(ff));
% Hltp_mod=20*log10(abs(Hltp(ff))); Hltp_angle=angle(Hltp(ff));
% Hlnp_mod=20*log10(abs(Hlnp(ff))); Hlnp_angle=angle(Hlnp(ff));
% 
% subplot(2,1,1);
% semilogx(ff,Hltp_mod,'b--',ff,Hlnp_mod,'b-',ff,Hltm_mod,'r--',ff,Hlnm_mod,'r-');
% legend('theoretical L1=50 cm','numerical filter above L1=50 cm','theoretical L1=5 cm','numerical filter L1=5 cm');
% xlabel('frequency (Hz)'); ylabel('amplitude (dB)'); 
% title('Losses coefficient with variation on L1');
% subplot(2,1,2);
% semilogx(ff,Hltp_angle,'b--',ff,Hlnp_angle,'b-',ff,Hltm_angle,'r--',ff,Hlnm_angle,'r-');
% xlabel('frequency (Hz)'); ylabel('phase');

%% Radiation filter with variations on r1

% [Hrtp,Hrnp]=rad_filter(r1*1.2,Fs,0.7,c,f);
% [Hrtm,Hrnm]=rad_filter(r1*0.8,Fs,0.7,c,f);
% 
% Hrtp_mod=20*log10(abs(Hrtp(ff))); Hrtp_angle=angle(Hrtp(ff));
% Hrnp_mod=20*log10(abs(Hrnp(ff))); Hrnp_angle=angle(Hrnp(ff));
% Hrtm_mod=20*log10(abs(Hrtm(ff))); Hrtm_angle=angle(Hrtm(ff));
% Hrnm_mod=20*log10(abs(Hrnm(ff))); Hrnm_angle=angle(Hrnm(ff));
% 
% subplot(2,1,1);
% semilogx(ff,Hrtp_mod,'b--',ff,Hrnp_mod,'r-',ff,Hrtm_mod,'b--',ff,Hrnm_mod,'r-');
% legend('theoretical 20% above r1','numerical filter 20% above r1','theoretical 20% under r2','numerical filter 20% under r2');
% xlabel('frequency (Hz)'); ylabel('amplitude (dB)'); 
% title('Radiation coefficient with 20% variation on r1=9.5mm, alpha=0.7');
% subplot(2,1,2);
% semilogx(ff,Hrtp_angle,'b--',ff,Hrnp_angle,'r-',ff,Hrtm_angle,'b--',ff,Hrnm_angle,'r-');
% xlabel('frequency (Hz)'); ylabel('phase');

%% Radiation filter with variations on alpha

[Hrtp,Hrnp]=rad_filter(r1,Fs,0.8488,c,f);
[Hrtm,Hrnm]=rad_filter(r1,Fs,0.6133,c,f);

Hrtp_mod=20*log10(abs(Hrtp(ff))); Hrtp_angle=angle(Hrtp(ff));
Hrnp_mod=20*log10(abs(Hrnp(ff))); Hrnp_angle=angle(Hrnp(ff));
Hrtm_mod=20*log10(abs(Hrtm(ff))); Hrtm_angle=angle(Hrtm(ff));
Hrnm_mod=20*log10(abs(Hrnm(ff))); Hrnm_angle=angle(Hrnm(ff));

subplot(2,1,1);
semilogx(ff,Hrtp_mod,'b--',ff,Hrnp_mod,'r-',ff,Hrtm_mod,'b--',ff,Hrnm_mod,'r-');
legend('theoretical, alpha = 0.8488','numerical, alpha = 0.8488','theoretical, alpha = 0.6133','numerical filter, alpha = 0.6133');
xlabel('frequency (Hz)'); ylabel('amplitude (dB)'); 
title('Radiation coefficient, r1=9.5mm, 0.6133<alpha<0.8488');
subplot(2,1,2);
semilogx(ff,Hrtp_angle,'b--',ff,Hrnp_angle,'r-',ff,Hrtm_angle,'b--',ff,Hrnm_angle,'r-');
xlabel('frequency (Hz)'); ylabel('phase');
