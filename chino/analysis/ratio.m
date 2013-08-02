function [Sratio] = ratio(r1,L1,L2)

c=343.54;  % sound speed
beta=0.003; % losses parameter

% x=rk in the function y

y=@(x)(1/r1*(L1+L2*sqrt((1+x)/(1-x)))*beta/(100*2*pi)*sqrt(2*c/(L1+L2))*(sqrt(1+acos(x)/pi)-2*sqrt(1-acos(x)/pi))+1-3*acos(x)/pi);
rk=fzero(y,0.5);
Sratio=sqrt((1+rk)/(1-rk));