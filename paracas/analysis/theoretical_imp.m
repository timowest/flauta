function [Z] = theoretical_imp_3tubes(p,f_use)

c=343.54;  % sound speed

L1=p(1); L2=p(2); L3=p(3); r1=p(4); r2=p(5); r3=p(6); beta=p(7);

S1=pi*r1^2; S2=pi*r2^2; S3=pi*r3^2;

%% With losses
k1=1i*2*pi*f_use/c+(1+1i)*beta/100*sqrt(f_use)/r1;
k2=1i*2*pi*f_use/c+(1+1i)*beta/100*sqrt(f_use)/r2;
k3=1i*2*pi*f_use/c+(1+1i)*beta/100*sqrt(f_use)/r3;

H1=exp(-k1*2*L1);
H2=exp(-k2*2*L2);
H3=exp(-k3*2*L3);

z3=(1+H3)./(1-H3);
R2=(S2/S3*z3-1)./(S2/S3*z3+1).*H2;
z2=(1+R2)./(1-R2);
R1=(S1/S2*z2-1)./(S1/S2*z2+1).*H1;
z1=(1+R1)./(1-R1);

Z=abs(z1);


