function [f_res] = faust_res(p,f_use)

Fs=44100;
N=Fs/10;
index=f_use*N/Fs;

L1=p(1); L2=p(2); r1=p(3); r2=p(4); beta=p(5);

system(sprintf('Faust/antara -length1 %f -length2 %f -radius1 %f -radius2 %f -coeflosses %f -n %d > Faust/antara.txt',L1,L2,r1,r2,beta,N));
[fid,~] = fopen('Faust/antara.txt','r');
out = fscanf(fid,'%g');
fclose(fid);
press=out(1:2:end);
Z=fft(hanning(N).*press);
Z=abs(Z(index));
Z=Z';

Y=1./Z;
Y_dB=20*log10(Y/norm(Y));
[~,ind]=findpeaks(Y_dB);
f_res=f_use(ind);
f_res=f_res(1:15);


end