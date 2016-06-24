close all
clear all
[x,fs,nbits]= wavread('taxi_honk.wav')
X = xcorr(x(:,1), x(:,2));
t = linspace(0,0.27,length(X));
figure
plot(t,X);
title('CH1 x CH2');
ylabel('Magnitude');
xlabel('Time (sec)');