clear all; close all;
clc;

r1=0.001:0.0001:0.020;
rat1=zeros(1,length(r1));
rat2=zeros(1,length(r1));
rat3=zeros(1,length(r1));

for k=1:length(r1)
    rat1(k)=ratio(r1(k),0.28,0.28);
    rat2(k)=ratio(r1(k),0.28,0.20);
    rat3(k)=ratio(r1(k),0.28,0.50);
end

r1=1000*r1;

plot(r1,rat1,'k-',r1,rat2,'r-',r1,rat3,'b-',r1,sqrt(3),'k-')
legend('configuration 1','configuration 2','configuration 3','lossesless optimal ratio')
xlabel('r1 (mm)');ylabel('ratio r1/r2');
title(sprintf('Radius ratio determined to harmonize the first two harmonics for several geometrical configurations'));

