clear all
close all

load('task4-3_data.mat');
%generating binary 
Y = de2bi(x(:))


for i = 1:size(Y-1,1)
%transposing the binary output to match w/ the input format for 
%bi2de function
Z = bi2de(Y.'); %converting the binary to dec
end

%print out the value
Z.'

