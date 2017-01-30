% Load results from HSPICE
x=loadsig('netlist.sw0');   % Change "netlist" to the appropriate name

% Assign different signals to variables
% (Use lssig(x) to list possible signals)
y=evalsig(x,'i_vsrc');
% For some reason I can't get the current to show correctly, so I have to
% invert it here (reversing the diode and/or source doesn't work)
y=-y; 
V=evalsig(x,'VOLTS');

% Plot results
%plot(V,y)
semilogy(V,abs(y)); grid
title('Va VS. log(I)')
xlabel('Applied Voltage (Volt)');
ylabel('Current (Amp)')
legend('show')
legend('Diode');