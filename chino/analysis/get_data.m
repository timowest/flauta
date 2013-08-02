function [Z] = get_data(path,f_use)

Fs=44100;
N=Fs/10;

[fid,~] = fopen(path,'r');
out = fscanf(fid,'%g');
fclose(fid);

f=out(1:3*10*Fs/N:end);
index=(f>=f_use(1))&(f<=f_use(end));

Z=abs(out(2:3*10*Fs/N:end)+1i*out(3:3*10*Fs/N:end));
Z=Z(index);