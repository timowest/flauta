function [out] = get_data_faust(p)

 a=dir(strcat('faust/',p));
 b={a(3:end).name};
 
out = zeros(22050,1);
 
 for k=1:length(b)
     file1=strcat('faust/',p,'/',char(b(k)));
     out = [out (csvread(file1))'];
 end
 
 out=out(:,2:end);