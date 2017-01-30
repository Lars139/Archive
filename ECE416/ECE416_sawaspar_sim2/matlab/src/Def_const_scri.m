%Def Const
EG  = 1.12;
kT  = 0.0259; 
ni  = 1.0e10;
k = 8.617e-5;
q = 1.6e-19;
T = 300;

ND  = [1e15 1e17 1e16 5e15];
NA  = [1e17 1e15 1e16 5e14];

Ksi   = 11.8;
Esp0  = 8.85e-14;

%Def Mobility Const
NDref = 6.948e-18;
NAref = 3.745e-18;
unmin = 88;
upmin = 54.3;
un0 = 1252;
up0 = 407;

%Dev Param
A  = 2e-4 * 1e-4;  %Unit in cm not um;
tau= 15e-6;
VA = linspace(-1.5,1.5);

