%%Author: Youthawin Philavastvanid (Bear) 
%%File  : ECE416_sim1_1.m
%%Date  : Oct 27, 2016
%%Desc  : Current Vs Voltage

%%Referred: ECE416_sim1_2.m

clear

%Defining Const
NDref = 6.948e-18;
NAref = 3.745e-18;
SiL = 0.5;
SiA = 1;
unmin = 88;
upmin = 54.3;
un0 = 1252;
up0 = 407;
ni = 1e10;
q = 1.60e-19;


ROH = [];

%Defining Dopants concentrations
N = [0 1.0e12 1.0e14 1.0e18];

%Calculating un, up
un = unmin + un0 ./ (1 + (N*NDref));
up = upmin + up0 ./ (1 + (N*NAref));

%Calculating Resistivity w/ respect to type
for i = 1:2
      roh = [0 0 0 0];
      if i == 1 %N-type: n = Nd
           n = N;
           roh = ((un.*n)*q).^-1;

      elseif i == 2 %P-type: p = Na
           p = N;
           roh = ((up.*p)*q).^-1;

      end

      %If n = 0 -> roh = Inf; Si is intrinsic
      temp = ((un*ni + up*ni)*q).^-1;
      roh(isinf(roh)) = temp(1);
      ROH = [ROH; roh];
end

R = ROH*SiL/SiA;
V = 0:0.1:10;
I = V./R(:);

hold all

%Plotting
close 

%plot(N, un, N, up);
title('Current Vs. Voltage');
loglog(V,I);
grid;
xlabel('Current (Amp)');
ylabel('Voltage (V)');
%legend('Nd=0', 'Nd=1e12', 'Nd=1e14', 'Nd=1e18', ...
%       'Na=0', 'Na=1e12', 'Na=1e14', 'Na=1e18');
legend('Nd=0', 'Na=0', 'Nd=1e12', 'Na=1e12', ...
       'Nd=1e14', 'Na=1e14', 'Nd=1e18', 'Na=1e18');
