function [ ] = lowcheck( )

freq = linspace(0, 10000, 1000);
 
R = 1000; %resistor value
C = 0.0000001; %capacitor value
 
% this for loop calculates gain for 1000 points between
% 0 and 10kHz
for x = 1:1000
    lowout(x) = ((1./(1+(((2.*j.*pi.*freq(x).*R.*C).^2)))));
end
 
% magnitude
lowoutlog = 10.*log10(abs(lowout));
% phase
phaseout = angle(lowout)*(-180/pi);
 
% magnitude plot
subplot(2,1,1);
semilogx(freq, lowoutlog);
title('Low Pass Filter Gain');
xlabel('Frequency');
ylabel('Gain (Decibels)');
axis([100,10000, -20,20]);
% phase plot
subplot(2,1,2);
semilogx(freq, phaseout);
title('Low pass phase');
xlabel('Freqency');
ylabel('Angle');
axis([100, 100000, -200, 10]);
 
end
