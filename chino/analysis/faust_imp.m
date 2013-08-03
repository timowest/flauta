function [Z] = faust_imp(p,f_use)

Fs=44100; % sample frequency
N=Fs;
index=f_use*N/Fs;

L1=p(1); L2=p(2); r1=p(3); r2=p(4); beta=p(5)/100;

system(sprintf('../resonator -res-len1 %f -res-len2 %f -res-rad1 %f -res-rad2 %f -res-losses %f -n %d > ../resonator.txt',L1,L2,r1,r2,beta,N));
[fid,~] = fopen('../resonator.txt','r');
out = fscanf(fid,'%g');
fclose(fid);
Z=fft(out);
Z=abs(Z(index));

end