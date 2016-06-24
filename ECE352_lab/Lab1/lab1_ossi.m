clear all
close all

rawData = xlsread('tek0000ALL.csv', 1,'A15:D10014');

figure
stairs(rawData(:,1),rawData(:,2), 'g'); %channel 1
title('Channel 1');
legend('More precise');
xlabel('Time (sec)');
ylabel('Voltage (mV)');

figure
stairs(rawData(:,1),rawData(:,3), 'b'); %channel 2\
title('Channel 2');
legend('Less precise');
xlabel('Time');
ylabel('Voltage (mV)');

%The lesser the Volt/Dev, the higher the precision/fedelity will be -- it
%will appear larger in the ossy screen.

%Make sure that the waveform takes up as much of the scope screen as
%possible while still being able to see the whole signal.