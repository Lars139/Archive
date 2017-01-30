% Gradian_scri.m
% Author: Bear
% Date : 28 Nov 2016
% Ref  : Book P.223

% Def Const
Def_const_scri

% Creating W w/ lenght of 2 units
Dev_Wp = linspace(-1,1);
Dev_Wl = 2;

% Calculation
% Doping it gradianly [ NC = ND-NA ] 
a  = (20^20);
NC = a*Dev_Wp; 
% Charge Density
roh = q*NC;
% E-field
Efield = (q*a/(2*Ksi*Esp0)) * (Dev_Wp.^2 - (Dev_Wl/2)^2);
% Eletrostatic Potential w/r Dev_p
Vx = (q*a/(6*Ksi*Esp0)) * ((2*(Dev_Wl/2)^3) + (3*(Dev_Wl/2)^2).*Dev_Wp - Dev_Wp.^3);

% Plotting
figure;
set(gcf,'units','normalized','outerposition',[0 0 0.5 1])
subplot(4,1,1);
plot(Dev_Wp, NC, 'b'); grid
title('Position vs Doping Concentration(cm^-^3)')
xlabel('Position (cm)')
ylabel('Doping Concentration (cm^-^3)')

subplot(4,1,2);
plot(Dev_Wp, roh, 'c'); grid
title('Position(cm) vs Charge Density(cm^-^3)')
xlabel('Position (cm)')
ylabel('Charge Density (cm^-^3)')

subplot(4,1,3);
plot(Dev_Wp, Efield, 'g'); grid
title('Position(cm) vs E-field(V/cm)')
xlabel('Position (cm)')
ylabel('E-field (V/cm)')

subplot(4,1,4);
plot(Dev_Wp, Vx, 'r'); grid
title('Position(cm) vs E-Potential(V)')
xlabel('Position (cm)')
ylabel('E-Potential (V)')


