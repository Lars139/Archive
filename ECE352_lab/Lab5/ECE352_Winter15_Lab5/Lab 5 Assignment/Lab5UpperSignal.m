close all

load('lab5_RedHerring.mat');

time_freq_plot(x,1024,44100);

z=filter(Num_c,1,x);

%Carrier Frequency
fc = 16200;

Z = z.*(cos(2*pi*fc*[1:length(z)]./Fs))'; %#ok<NBRAK>

time_freq_plot(Z,1024,Fs);

Y = filter(Num_1,1,Z);
time_freq_plot(Y,1024,Fs);

%sound(Y,Fs);

%a=1;