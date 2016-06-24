clear all
close all

load('task4-1_data.mat');
X = fft(x)
subplot(2,2,1)
plot(x(1,:));
subplot(2,2,2)
plot(X(1,:));
subplot(2,2,4)

plot(x(2,:));
subplot(2,2,3)
plot(X(2,:));
subplot(2,2,4)
