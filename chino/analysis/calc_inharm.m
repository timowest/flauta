function [p,dist] = calc_inharm(Y,f_use,partial)

[~,ind]=findpeaks(Y,'MINPEAKHEIGHT',-30);
f_res=f_use(ind);
p=partial(1:length(f_res));
dist=f_res./(f_res(1)*p);

end