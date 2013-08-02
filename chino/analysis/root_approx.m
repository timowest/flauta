function [B0,B1,B2,B3,A1,A2,A3] = root_approx(f_range,Fs)

Fmin=f_range(1);
Fmax=f_range(end);
wU=2*pi*sqrt(Fmin*Fmax);
alpha=(Fmax/Fmin)^(1/6);

a0=1+2*Fs/(wU*alpha^(1/2));
a1=1-2*Fs/(wU*alpha^(1/2));
b0=1+2*Fs/(wU*alpha^(-1/2));
b1=1-2*Fs/(wU*alpha^(-1/2));

aa0=1+2*Fs/(wU*alpha^(5/2));
aa1=1-2*Fs/(wU*alpha^(5/2));
bb0=1+2*Fs/(wU*alpha^(3/2));
bb1=1-2*Fs/(wU*alpha^(3/2));

aaa0=1+2*Fs/(wU*alpha^(-3/2));
aaa1=1-2*Fs/(wU*alpha^(-3/2));
bbb0=1+2*Fs/(wU*alpha^(-5/2));
bbb1=1-2*Fs/(wU*alpha^(-5/2));

A0=a0*aa0*aaa0;
A1=(a1*aa0*aaa0+a0*aa1*aaa0+a0*aa0*aaa1)/A0;
A2=(a0*aa1*aaa1+a1*aa0*aaa1+a1*aa1*aaa0)/A0;
A3=(a1*aa1*aaa1)/A0;

factor=sqrt(wU)*alpha^(-3/2)/A0;

B0=(b0*bb0*bbb0)*factor;
B1=(b1*bb0*bbb0+b0*bb1*bbb0+b0*bb0*bbb1)*factor;
B2=(b0*bb1*bbb1+b1*bb0*bbb1+b1*bb1*bbb0)*factor;
B3=(b1*bb1*bbb1)*factor;

end