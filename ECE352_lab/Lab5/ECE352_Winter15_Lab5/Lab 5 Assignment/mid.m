close all
clear all

%Define sampling freq
Fs = 44100;

%Loading the RedHerring
load('lab5_RedHerring.mat');
load('BP1.mat');
load('BP2.mat');

time_freq_plot(x,1024,44100);
z=filter(BP1,1,x);

%Shift the freq 
%Carrier Frequency
fc = 10500;
%for rad = 0:pi/10:2*pi

%{
For Red Harring,  rad = pi/10;
For Secret Msg,   rad = 6pi/10; 
%}
rad = pi/10;
Z = z.*(cos(2*pi*fc*[1:length(z)]./Fs +rad ))'; 
time_freq_plot(Z,1024,Fs);

Y = filter(BP2,1,Z);
time_freq_plot(Y,1024,Fs);
tlt = sprintf('Degree: %d',rad/pi);
title(tlt)

sound(Y,Fs);
%pause
%end









