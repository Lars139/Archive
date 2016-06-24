close all
clear all

%Define freq
Fs = 44100;
fnq = 22050;

%Loading the RedHerring
load('lab5_RedHerring.mat');
load('LP_Filt.mat');
load('LP1_Filt.mat');

time_freq_plot(x,1024,44100);
z=filter(LP1,1,x);

%Carrier Frequency
fc = 4700;
Z = z.*(cos(2*pi*fc*[1:length(z)]./Fs))'; 
time_freq_plot(Z,1024,Fs);
Y = filter(LP1,1,Z);
time_freq_plot(Y,1024,Fs);

sound(Y,Fs);

%a=1;

