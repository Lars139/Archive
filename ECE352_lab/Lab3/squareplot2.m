function [ ] = squareplot2(TIME, CH1, CH2, CH3 )
% 100Hz version
MTX = xlsread('tek0000ALL.csv');
TIME = MTX(:,1);
CH1 = MTX(:,2);
CH2 = MTX(:,3);

MTX2= xlsread('tek0003ALL.csv');
TIME2=MTX(:,1);
CH3 = MTX2(:,3);

subplot(3,1, 1);
plot(TIME, CH1);
title('100Hz Square Wave Input');
ylabel('Volts');
xlabel('s');
subplot(3,1, 2);
plot(TIME, CH2);
title('Low Pass Filter Response');
ylabel('Volts');
xlabel('s');
subplot(3,1, 3);
plot(TIME, CH3);
title('High Pass Filter Response');
ylabel('Volts');
xlabel('s');
end