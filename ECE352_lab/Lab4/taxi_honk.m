%pre_lab for lab 4
clear all
close all

[honk,fs,nbits]=wavread('taxi_honk.wav');

[honk_corr, m_shift, m_x] = cross_corr(honk(:, 1), honk(:, 2));

t_shift = (m_shift/fs)*10^3;  %t_shift in millisec
figure
plot(t_shift, honk_corr)
xlabel('time shift in (ms)')
title('Cross-Correlation of CH1 and CH2 for taxi-honk recording')
figure
plot(t_shift, honk_corr)
xlim([0 10])
xlabel('time shift in (ms)')
title({'Cross-Correlation of CH1 and CH2 for taxi-honk recording'...
      'Close-Up'});