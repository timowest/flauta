function [Z] = faust_imp(p,f_use)

Fs=44100; % sample frequency
N=Fs/10;
index=f_use*N/Fs;

L1=p(1); L2=p(2); L3=p(3); r1=p(4); r2=p(5); r3=p(6); beta=p(7)/100;
system(sprintf('../resonator -res-len1 %f -res-len2 %f -res-len3 %f -res-rad1 %f -res-rad2 %f -res-rad3 %f -res-losses %f -n %d > ../resonator.txt',L1,L2,L3,r1,r2,r3,beta,N));
[fid,~] = fopen('../resonator.txt','r');
out = fscanf(fid,'%g');
fclose(fid);

%output 1 : acoustic velocity
%output 2 and 3 : acoustic pressure

press=out(2:3:end); 
Z=fft(hanning(N).*press);
Z=abs(Z(index));

end