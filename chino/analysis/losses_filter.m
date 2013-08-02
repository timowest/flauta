function [Ht,Hn] = losses_filter(p,Fs,f)

%L1=p(1); L2=p(2); r1=p(3); r2=p(4); beta=p(5);
L1=p(1); r1=p(2); beta=p(3);
K=2*(L1/r1);

%% Losses : numerical filter
[B0,B1,B2,B3,A1,A2,A3]=root_approx(f,Fs);
Dn=freqz([B0,B1,B2,B3],[1,A1,A2,A3],f,Fs);
Hn=(1-beta/100*K*Dn/(2*sqrt(pi)))./(1+beta/100*K*Dn/(2*sqrt(pi)));

%% Losses : theoretical filter
Ht = exp(-(1+1i)*beta/100*K*sqrt(f));

%% Losses : analogical approximation 1 and 2 orders
 %wU=2*pi*sqrt(f(1)*f(end));
 %alpha=(f(end)/f(1))^(1/6);
 
 %H0a=freqs([1/(alpha^(-1/2)*wU) 1],[1/(alpha^(1/2)*wU) 1],2*pi*f);
 %H1a=freqs([1/(alpha^(3/2)*wU) 1],[1/(alpha^(5/2)*wU) 1],2*pi*f);
 %Hminus1a=freqs([1/(alpha^(-5/2)*wU) 1],[1/(alpha^(-3/2)*wU) 1],2*pi*f);
 
 %Da1=H0a.*H1a.*Hminus1a*alpha^(-3/2)*sqrt(wU);
 %Ha1=1-beta*K*Da1/sqrt(pi);
 
 %H2a=freqs([1 0],[0 1],w);
 %Ha2=Ha1+(beta*K)^2/pi*H2a/(2*pi);

end
