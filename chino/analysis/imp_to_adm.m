function [Y] = imp_to_adm(Z)

Y=1./Z;
Y=20*log10(Y/norm(Y));

end