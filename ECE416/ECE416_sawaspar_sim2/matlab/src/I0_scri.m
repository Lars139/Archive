% I0.m
% Author: Bear
% Date: 18 Nov 2016
% Ref : Book P.253

% Calling Vbi_scri
% Vbi_scri

%Calculating
un = unmin + un0 ./ (1 + (ND*NDref));
up = upmin + up0 ./ (1 + (NA*NAref));

DP = k.*T.*up;
DN = k.*T.*un;
LP = sqrt(DP.*tau);
LN = sqrt(DN.*tau);
I0 = q.*A.*((DN./LN).*(ni^2./NA) + (DP./LP).*(ni^2./ND));
I  = I0.'*(abs(exp(VA./(k.*T))-1));