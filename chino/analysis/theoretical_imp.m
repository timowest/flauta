function [Zw,Z] = theoretical_imp(p,f_use)

c=343.54;  % sound speed

L1=p(1); L2=p(2); r1=p(3); r2=p(4); beta=p(5);

rk=(r1^2-r2^2)/(r1^2+r2^2);

%% Without losses
kw=2*1i*pi*f_use/c;
H1w=exp(-kw*2*L1);
H2w=exp(-kw*2*L2);
Zw=(1+rk*(H1w+H2w)+(H1w.*H2w))./(1+rk*(H2w-H1w)-(H1w.*H2w));
Zw=abs(Zw);

%% With losses
k1=1i*2*pi*f_use/c+(1+1i)*beta/100*sqrt(f_use)/r1; % with losses propagation
k2=1i*2*pi*f_use/c+(1+1i)*beta/100*sqrt(f_use)/r2; % with losses propagation

H1=exp(-k1*2*L1);
H2=exp(-k2*2*L2);
Z=(1+rk*(H1+H2)+(H1.*H2))./(1+rk*(H2-H1)-(H1.*H2));
Z=abs(Z);
