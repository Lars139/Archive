function time_freq_plot(x,window_size,Fs)
% This function creates a time-vs-frequency plot image for analyzing a signal's time-evolving
% frequency content. The signal is x, an analysis window of window_size samples is stepped
% through the time extent of the signal, and Fs is the sample rate in Hz. A color-coded
% logarithmic plot is generated of the top 30 dB of the frequency response magnitude; a color
% bar at the bottom left of the plot shows the color-coding of the dB values. The time waveform
% x is plotted to the left of the time-frequency plot that coincides with the center time
% of the analysis window used to produce the time-vs-frequency plot to the right.

N=length(x); % number of data samples
n_anal=window_size;
n_step=n_anal/4;
n_specdisplay=fix((N-n_anal)/n_step);
%disp(['This choice will generate ',int2str(n_specdisplay),' displayed gram lines.'])
gram=zeros(n_specdisplay,n_anal);  % pre-assign 2-D size of gram display
%disp('A Hamming window will be used to suppress the sidelobe artifacts.')
window=hamming(n_anal);
n=1:n_anal;
for k=1:n_specdisplay
    gram(k,:)=abs(fft(window.*x(n)))';
    n=n+n_step;
end

Ts=1/Fs;    % sampling interval in seconds
[n_rows,n_cols]=size(gram);

dB_range = 30; % dynamic range in dB to plot with color scale

log_gram = 10*log10(gram(:,1:n_cols/2 + 1)); % extract only the positive frequency half
log_gram = log_gram - max(max(log_gram));
vec = find(log_gram < (-dB_range));
log_gram(vec) = -dB_range*ones(size(vec));

fig1 = figure('PaperOrientation','portrait',...
              'PaperPosition',[1.1,1,6.5,9],...
              'Position',[10,10,820,620],...
              'Units','pixel');

fmax=Fs/2000;                                  % max frequency in KHz
tmax = fix((n_rows-1)*n_step*Ts*1000 + .5);    % max time in milliseconds
axwidth = .78;
f_axis = (0:n_cols/2)*(Fs/(1000*n_cols));

ax_title = axes('Position',[.2,.97,axwidth,1],...
                'Units','normalized',...
                'Visible','off');
% Figure title
title_text = text('Position',[.5,0],...
                  'Units','normalized',...
                  'FontSize',[14],...
                  'HorizontalAlignment','center',...
                  'VerticalAlignment','bottom',...
                  'String','TIME - VS - FREQUENCY  PLOT  IMAGE  OF  LAB  5  DATA');

% Time-vs-frequency gram plot
axbottom = .15;
axheight = .79;
XX = [0;1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19;20;21;22];
ax1 = axes('Position',[.2,axbottom,axwidth,axheight],...
           'Units','normalized',...
           'FontSize',[12],...
           'Box','on',...
           'TickDir','out',...
           'NextPlot','add',...
           'XGrid','off',...
           'XLim',[0,fmax],...
           'XTick',XX,...
           'YLim',[0,tmax]);
% selection = input('Enter 0 for gray scale, 1 for color scale: ');
selection=1;
if selection == 0
    colormap(gray(256));
else
    map = hsv(329);
    colormap(map(256:-1:1,:));
end
title('FFT-BASED SPECTRAL  ANALYSIS')
set(ax1,'FontSize',[9])
t_axis = (0:n_rows - 1)*n_step*Ts*1000;
xlabel('Frequency  (KHz)')
ylabel('Center Time of Analysis Window  (ms)')
imagesc(f_axis,t_axis,log_gram)

% Signal-vs-time plot to left of time-vs-frequency gram plot
tover = fix((n_anal/2)*Ts*1000 + .5);
t_height = ((tmax + 2*tover)/tmax)*axheight;
t_bottom = axbottom - (t_height - axheight)/2;
x_max=max(abs(x));
ax2 = axes('Position',[.01,t_bottom,.11,t_height],...
           'Units','normalized',...
           'Box','on',...
           'NextPlot','add',...
           'FontSize',[9],...
           'XLim',[-x_max,x_max],...
           'XDir','reverse',...
           'YTickLabelMode','manual',...
           'YTickLabel',[],...
           'YLim',[-tover,tmax+tover]);
t_axis = (-n_anal/2:n_anal/2-1+(n_rows - 1)*n_step)*Ts*1000;
plot(x(1:1 + (n_rows - 1)*n_step + n_anal - 1),t_axis,'b')
xlabel('Signal Amplitude')
line([.6*x_max,.6*x_max],[(-n_anal/2)*Ts*1000,(n_anal/2)*Ts*1000])
line([.65*x_max,.55*x_max],[0,0])

% Color bar legend on left bottom
ax5 = axes('Position',[.15,.03,.02,.10],...
           'Units','normalized',...
           'Box','on',...
           'NextPlot','add',...
           'FontSize',[9],...
           'TickDir','out',...
           'XTickLabelMode','manual',...
           'XTickLabel',[],...
           'XLim',[1,2],...
           'YLim',[-dB_range,0]);
vec = (-dB_range:0)';
barr = [vec vec];
imagesc((1:2),(-dB_range:0),barr)
ylabel('dB colormap')
%