function [Z] = get_data(path,f_use)

Fs=44100;
N=Fs/10;

[fid,~] = fopen(path,'r');
out = fscanf(fid,'%g');
fclose(fid);

f=round(out(1:2*2*Fs/N:end));
index=(f>=f_use(1))&(f<=f_use(end));

Z=out(2:2*2*Fs/N:end);
Z=Z(index);