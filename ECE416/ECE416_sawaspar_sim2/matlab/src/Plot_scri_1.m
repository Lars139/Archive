% Plotting V-I graph for a different doping profile
fig_tau = figure;
set(gcf,'units','normalized','outerposition',[0.5 0.0 0.325 0.5])
semilogy(VA,I); grid
title('Va VS. log(I)')
xlabel('Applied Voltage (Volt)');
ylabel('Log(I) (Amp)')
legend('show')
legend('tau=15e-6', 'tau=100e-6', 'tau=150e-6');
