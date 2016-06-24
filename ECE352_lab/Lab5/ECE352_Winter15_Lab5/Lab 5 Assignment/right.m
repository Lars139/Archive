close all
clear all

%Define sampling freq
Fs = 44100;

%Loading the RedHerring
load('lab5_RedHerring.mat');
load('HP1.mat');
load('LP2.mat');

time_freq_plot(x,1024,44100);
z=filter(HP1,1,x);

%Shift the freq 
%Carrier Frequency
fc = 16190;

Z = z.*(cos(2*pi*fc*[1:length(z)]./Fs))'; 
time_freq_plot(Z,1024,Fs);

Y = filter(LP1,1,Z);
time_freq_plot(Y,1024,Fs);

sound(Y,Fs);

