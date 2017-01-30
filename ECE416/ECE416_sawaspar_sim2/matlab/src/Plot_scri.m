%Plotting Vbi_scri (only for testing purpose)
plot(NC, Vbi); grid
xlabel('Charge Carrier Concentration (cm-3)');
ylabel('Vbi (volts)')
text(6e11,0.66,'Si 300K')
close

% Plotting V-I graph for a different doping profile
set(gcf,'units','normalized','outerposition',[0.5 0.5 0.325 0.5])
semilogy(VA,I); grid
title('Va VS. log(I)')
xlabel('Applied Voltage (Volt)');
ylabel('Log(I) (Amp)')
legend('show')
legend('Na=1e17 Nd=1e15', 'Na=1e17 Nd=1e15', 'Na=1e16 Nd=1e16', 'Na=5e15 Nd=5e14');

% Plotting Capacitance at a different voltage from [-1.5, 1.5] of a different doping profile
figure
semilogy(VA,Cv1); grid
set(gcf,'units','normalized','outerposition',[0.5 0.0 0.325 0.5])
title('Va VS. log(C)')
xlabel('Applied Voltage (Volt)');
ylabel('Capacitance (F)')
legend('show')
legend('Na=1e17 Nd=1e15', 'Na=1e17 Nd=1e15', 'Na=1e16 Nd=1e16', 'Na=5e15 Nd=5e14');

% Printing out the table for all the calculated value
Const_disp_tabl = table(ND.', NA.', NC.', Vbi.', I0.', Cv0.', Cvr3.');
Const_disp_tabl.Properties.VariableNames = {'Nd' 'Na' 'NC' 'Vbi' 'I0' 'Cv0' 'CvRev3'}
disp('    (cm-3)   (cm-3)     (cm-3)       (V)           (A)           (F)           (F)');

