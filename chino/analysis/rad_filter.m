function [Hn] = rad_filter(r1,Fs,rad_coef,c,f)

%% Radiation : theoretical
k=2*pi*f/c;
Z=1/4*(k*r1).^2+1i*rad_coef*(k*r1);
Ht=(Z-1)./(Z+1);

%% Radiation : numerical filter
% A=(r1*Fs/c)^2;
% B=2*rad_coef*r1*Fs/c;
% 
% p0=(A+1+2*r1*Fs/c*sqrt(1+rad_coef^2))/(A-B-1);
% p1=(A+1-2*r1*Fs/c*sqrt(1+rad_coef^2))/(A-B-1);
% 
% a0=p0;
% a1=-(1+p0*p1);
% a2=p1;
% 
% b0=-A+B-1;
% b1=2*A-2;
% b2=-1-A-B;

A=(r1*Fs/(2*c))^2;
B=rad_coef*r1*Fs/c;

a0=A-B-1;
a1=B-2*A;
a2=A;

b0=A+1-B;
b1=B-2*A;
b2=A;

Hn=freqz([b0/a0 b1/a0 b2/a0],[a0/a0 a1/a0 a2/a0],f,Fs);

end

