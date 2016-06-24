function [ ] = HighPass( )

freq = linspace(0, 100000, 100000);
 Resistor = 1000;
 Cap = 0.0000001;

 %complex number for each frequency iteration
for x = 1:100000
    highpass(x) = ((((2.*j.*pi.*freq(x))^2).*((Resistor.*Cap).^2))./....
                  ((3.*(2.*j.*pi.*freq(x)).*(Resistor.*Cap))+1+((((2.*j.*pi.*freq(x))^2).*((Resistor.*Cap).^2)))));
end

%converts complex number to MAG (20 dB/DEC) and Phase(angle)
highpass_MAG_dB = 20.*log10(abs(highpass));
phase = angle(highpass).*180/pi;


subplot(2,1,1);
semilogx(freq, highpass_MAG_dB);
title('High Pass Gain');
xlabel('Freq. (Hz)');
ylabel('Gain (dB)');
axis([10,100000, -150,0]);
% phase plot
subplot(2,1,2);
semilogx(freq, phase);
title('High Pass phase');
xlabel('Freq. (Hz)');
ylabel('Angle (Degrees)');
axis([10, 100000, 0, 180]);
 
 
end
