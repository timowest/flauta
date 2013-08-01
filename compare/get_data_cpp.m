function [out] = get_data_cpp(p)

 a=dir(strcat('cpp/',p));
 b={a(3:end).name};
 
out = zeros(22050,1);
 
 for k=1:length(b)
     file1=strcat('cpp/',p,'/',char(b(k)));
     out = [out (csvread(file1))'];
 end
 
 out=out(:,2:end);