function lab1_audio(filename)
%close all
%clear all
[Y,Fq,~] = wavread(filename);
%sound(Y(:,2), Fq);
sound(Y(:,1),Fq);
Ori_samp_16_22 = Y(:,:).*2^15;

t = linspace(0, 0.04, length(Ori_samp_16_22));
figure
hold all
subplot(2,1,1);
plot(t, Ori_samp_16_22(:,1) );
title('Channel 1')

subplot(2,1,2);
plot(t, Ori_samp_16_22(:,2),'g');
title('Channel 2')
xlabel('Time (sec)')
ylabel('Magnitude')

ha = axes('Position',[0 0 1 1],'Xlim',[0 1],'Ylim',[0 1],'Box','off','Visible','off','Units','normalized', 'clipping' , 'off');

text(1, 1,filename,'HorizontalAlignment' ,'right','VerticalAlignment', 'top')
end



% 80% for the full volume, 40% for the half volume

% We can hear differences between the different sample and frequency
% settings but cannot see them in the plots. In future audio recordings,
% we should use 16bit, 22kHz, full volume

% In future audio recordings, we should use 16bit, 22kHz, full volume.