%%Author: Youthawin Philavastvanid (Bear) 
%%File  : ECE416_sim1_1.m
%%Date  : Oct 23, 2016
%%Desc  : Energy level VS. Electron Occupants

%%Referred: Pierret Book, 2nd Edition, P. 45

%Defining Const
k = 8.617e-5;
tmp = [0.01, 100, 200, 300, 400];

%Computation 
for ii= 1:5;
    T = tmp(ii);
    kT = k*T;
    dE(ii,1) = -5*kT;
    for jj = 1:101
        f(ii,jj) = 1/(1 + exp(dE(ii,jj)/kT));
        dE(ii,jj+1) = dE(ii,jj) + 0.1*kT;
    end
end
dE = dE(:,1:jj);

%Plot the graphs
close

plot(dE',f'); 
title('Energy Level Vs. Occupation Probability');
grid;
xlabel('E-EF(eV)');
ylabel('f(E)');
text(0.05, 0.2, 'T=400K');
text(-0.03, 0.1, 'T=0.01K');
