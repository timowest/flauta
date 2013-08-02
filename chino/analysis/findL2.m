clear all; close all;
clc;

r1=0.0095;
r2opt=r1/sqrt(3);
r2=r2opt*0.8:0.0001:r2opt;
L2=zeros(1,length(r2));

for k=1:length(r2)
    L2(k)=length2(r1,r2(k),0.28);
end

plot(r2*1000,L2)
%legend('configuration 1','configuration 2','configuration 3','configuration 4','lossesless ratio')
xlabel('r2 (mm)');ylabel('L2');
%title(sprintf('Radius ratio determined to harmonize the first eigen \n frequencies for several geometrical configurations'));