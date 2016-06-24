%6.1  Task:  
%Determine Lightning Strike Location from Recorded Thunderstorm Data .
%NOTE: files in wavread are in current directory
close all
clear all

[data_A, Fs, nbits] = wavread('rain_A_site.wav');
[data_B, ~, ~] = wavread('rain_B_site.wav');
%using suggested sample index for audio file (i.e.: where the thunder...
                                              ...is)
%sample indecies 22000 -> 42000
A_ch1 = data_A(22000:42000, 1);
A_ch2 = data_A(22000:42000, 2);
B_ch1 = data_B(22000:42000, 1);
B_ch2 = data_B(22000:42000, 2);

[A_cor, ~, m_Apeak] = cross_corr(A_ch1, A_ch2);
[B_cor, m, m_Bpeak] = cross_corr(B_ch1, B_ch2);

t_shift = (m/Fs)*10^3;  %see taxi_honk

figure
subplot(2,2,1); plot(t_shift, A_cor); 
title('Correlation of site A');xlabel('Time shift in ms');
subplot(2,2,2); plot(t_shift, B_cor); 
title('Correlation of site B');xlabel('Time shift in ms');
subplot(2,2,3); plot(t_shift, A_cor);
xlim([-1 1]);
title('Close up of correlation for site A');
xlabel('Time shift in ms');
subplot(2,2,4); plot(t_shift, B_cor);
xlim([-1 1]);
title('Close up of correlation for site B');
xlabel('Time shift in ms');

%finding the incident angle for each site
%NOTE: d = spacing of two microphones at one site = 1km for this example
d = 1;

theta_A = incident_angle(m_Apeak, Fs, d);
theta_B = incident_angle(m_Bpeak, Fs, d);


%finding the distance to source from each 
s = 1;  %distance from site A to site B in kilometers
[dis_A, dis_B] = locate_src(theta_A, theta_B, s); %distances in km
figure
plot(A_ch1)
title('Channel 1');
figure
plot(A_ch2)
title('Channel 2');
figure
plot(data_A)
title('Overlapping Processed Channel');

