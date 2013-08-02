function[Ys]=faust_adm_square(p,Yexp)

Fs=44100; % sample frequency
N=Fs/10; % output length
f_range=20:5600; % useful frequency range
f_use=f_range(1:Fs/N:end);

Z=faust_imp(p,f_use);
Y=imp_to_adm(Z');
Ys=Y.*Yexp;

end

