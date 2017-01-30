% Cap_scri.m
% Author: Bear
% Date  : 21 Nov 2016

% Calling  I0_scri.m to find out Vbi
%I0_scri

% Calculating W @ Va = 0
Va = 0;
W = ((2*Ksi*Esp0/q)*((NA + ND)/(NA.*ND))*(Vbi-Va)).^(1/2);
% Calculating C @ Va = 0
Cv0 = (Ksi*Esp0*A)./(W);

% Calculating W @ Va = -3
Va = -3;
W = ((2*Ksi*Esp0/q)*((NA + ND)/(NA.*ND))*(Vbi-Va)).^(1/2);
% Calculating C @ Va = 0
Cvr3 = (Ksi*Esp0*A)./(W);

% Calculating W for VA = [-1.5, 1.5]
W = ((2*Ksi*Esp0/q)*((NA + ND)/(NA.*ND))*(Vbi-VA.')).^(1/2);
% Calculating C for VA = [-1.5, 1.5]
Cv1 = (Ksi*Esp0*A)./abs(W);