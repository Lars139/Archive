%%Author: Youthawin Philavastvanid (Bear) 
%%File  : ECE416_sim1_1.m
%%Date  : Oct 23, 2016
%%Desc  : Mobility VS. Dopant Concentration

%%Referred: Pierret Book, 2nd Edition, P. 84

%Defining Const
NDref = 6.948e-18;
NAref = 3.745e-18;
unmin = 88;
upmin = 54.3;
un0 = 1252;
up0 = 407;

%Mobility Calculation
N = logspace(12,20);
un = unmin + un0 ./ (1 + (N*NDref));
up = upmin + up0 ./ (1 + (N*NAref));

%Plotting
close 

loglog(N, un, N, up);
grid;
axis([1.0e12 1.0e20 1.0e1 1.0e4]);
xlabel('NA or ND (cm-3)');
ylabel('Mobility (cm2/V-sec)');
text(1.0e15, 1500, 'Electrons');
text(1.0e15, 500, 'Holes');
text(1.0e18, 2000, 'Si, 300K');
