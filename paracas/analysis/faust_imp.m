function [Z] = faust_imp(p,f_use)

Fs=44100; % sample frequency
N=Fs/10;
index=f_use*N/Fs;

L1=p(1); L2=p(2); r1=p(3); r2=p(4); beta=p(5);

system(sprintf('../gen/resonator -length1 %f -length2 %f -radius1 %f -radius2 %f -coeflosses %f -n %d > ../gen/resonator.txt',L1,L2,r1,r2,beta,N));
[fid,~] = fopen('Faust/resonator.txt','r');
out = fscanf(fid,'%g');
fclose(fid);

%output 1 and 3 : acoustic pressure
%output2 : acoustic velocity

press=out(1:3:end); 
Z=fft(hanning(N).*press);
Z=abs(Z(index));

end